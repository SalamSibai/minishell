/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/22 20:20:38 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/param.h>
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include <sys/wait.h>

# define BUFF_SIZE 4096

typedef enum e_token_type
{
	CMDS,				//0
	PIPE,				//1
	LIMITER,			//2
	FILE_NAME,  		//3
	REDIRECT_INPUT,		//4
	REDIRECT_OUTPUT,	//5
	HEREDOC,			//6
	REDIRECT_APPEND,	//7
	REDIR_INPUT_FAILED,
	REDIR_OUTPUT_FAILDED,
	FLAG,				//8
	ID,					//9
	EXEC_ID,			//10
	DQOUTES,			//11
	SQOUTES,			//12
	NONE				//13
} e_token_type;

/*
* 	The pipe structure, which indludes:
* 	1) the pipes (both of them)
* 	2) the pids of the forked processes
* */
typedef struct s_pipe
{
	int	fd[2][2];
	int	*pid;
}	t_pipe;

/// @brief the redirection struct
typedef struct s_redirection
{
	//int						fd;
	e_token_type			type;
	char					*file_name;
	char					*limiter;
	struct s_redirection	*next;	//TYPE LIST
}	t_redirection;

/// @brief 
typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			*cmd_path;
	char			*cmd_str;
	char			**cmd_with_flag;
	char			*flag;
	char			*args_str;
	t_list			*args;
	t_redirection	*redirection;
}	t_cmd;

/// @brief Stores information on tokens
typedef struct s_token
{
	char			*token_string;
	e_token_type	type;
}				t_token;


typedef struct s_lexer
{
	int	n_cmds;
	int	n_pipes;
	int	n_redirections;
	int	n_tokens;
}	t_lexer;

typedef struct s_data
{
	int			cmd_num;
	int			cmd_ctr;
	int			origin_fds[2];
	t_list		*env;
	t_list		*export_env;
	t_cmd		**cmds;
	t_token		**tokens;
	t_pipe		*pipe;
	char		**env_var;
	char		**path;
	char		*buf;
}	t_data;


/* ************************************************************************** */
/*								SYNTAX VALIDATION							  */
/* ************************************************************************** */
bool			validate_syntax(char *line);
bool			validate_unbalanced_qoutes(char *line);
bool			validate_tokens(t_data *data);
bool			validate_pipes(char *line);
bool			validate_id(int index, t_data *data);
bool			validate_pipe(t_token **tokens, int index);
bool			validate_input_redirection(t_token **tokens, int index);
bool			validate_output_redirection(t_token **tokens, int index);
bool			validate_qoutes(int index, t_data *data);

void			alloc_pids(t_data *d);
bool			make_pipes(t_pipe *p);

/* ************************************************************************** */
/*									PARSEING								  */
/* ************************************************************************** */
void			scan(char *av, t_token **tokens);
void			init_cmds(t_data *data);
void			set_cmds(t_data *data);
int				count_cmds(t_token **tokens);

/* ************************************************************************** */
/*									PARSE UTILS								  */
/* ************************************************************************** */
int				ft_panic(char *message, int ret);
void			*ft_safe_malloc(size_t size, char *msg);

/* ************************************************************************** */
/*									TOKENS UTILS							  */
/* ************************************************************************** */
void			set_type(t_token *token);
int				token_count(char *av);
bool			is_cmd(char *cmd, t_data *data);

/* ************************************************************************** */
/*									REDIRECTION								  */
/* ************************************************************************** */
t_redirection	*redir_new(int fd, e_token_type type, char *file_name, char *limiter);
t_redirection	*redir_last(t_redirection *redir);
void			redir_add_back(t_redirection **redir, t_redirection *new);
void			redir_add_front(t_redirection **redir, t_redirection *new);
void			redir_clear(t_redirection **redir);
void			check_redirections(t_cmd **cmds);
void			check_type(t_cmd *cmd);
bool			get_input(t_cmd *cmd, bool heredoc, t_redirection *redir);
bool			set_output(t_cmd *cmd, bool append, t_redirection *redir);
bool			redirect_fds(t_data *data,t_cmd *cmd, int i, int j);
bool			redirect_file_input(t_cmd *cmd);
bool			redirect_pipe_input(t_pipe *pipe, int j);
bool			redirect_file_output(t_cmd *cmd);
bool			redirect_pipe_output(t_pipe *pipe, int j);
bool			redirect_stdin(t_data *data, t_cmd *cmd);
bool			redirect_stdout(t_data *data, t_cmd *cmd);

/* ************************************************************************** */
/*									EXPANSION								  */
/* ************************************************************************** */
t_token			**check_expandable_var(t_token **tokens, t_list *env);

/* ************************************************************************** */
/*									PATH									  */
/* ************************************************************************** */
char			**set_path(char **envp, t_data *data);
bool			get_path(t_data *data, t_cmd *cmd);

/* ************************************************************************** */
/*									ENVIROMENT								  */
/* ************************************************************************** */
t_list			*env_init(char **envp);
t_list			*export_env_init(t_list *env);
char			**env_to_str(t_list *env);
bool			is_valid_env(const char *var);
char			*add_quotes(char *value);
bool			is_in_env(t_list *env, char *args);
char			*get_env_name(char *dest, const char *src);
void			print_env(t_list *env, bool export, int fd);
bool			print_error(const char *arg);

/* ************************************************************************** */
/*									BUILTINS								  */
/* ************************************************************************** */
int				ft_cd(t_cmd *cmd, t_list *env);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_list *env, int fd);
bool			ft_export(t_cmd *cmd, t_list *export_env, t_list *env);
int				ft_pwd(int fd);
int				ft_unset(t_list *args, t_list *env);

/* ************************************************************************** */
/*									EXECUTION								  */
/* *********************************************************************** */
bool			is_builtin(char *command);
bool			is_env_builtin(char *command);
int				exec_builtin(t_cmd *cmd, t_data *data);
void			execute_cmds(t_data *data);
void			execution(t_data *data);
bool			join_cmd_and_flag(t_cmd *cmd);

/* ************************************************************************** */
/*									DEBUG									  */
/* ************************************************************************** */
void			print_data(t_data *data);

/* ************************************************************************** */
/*								Error Handling								  */
/* ************************************************************************** */
void			free_data(t_data *data);
bool			close_fd(int fd);
bool			close_fds(t_data *data, int i);

//Creating a tree, where the left branch will be executed first.
#endif