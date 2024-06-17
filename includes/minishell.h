/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/18 01:25:41 by mohammoh         ###   ########.fr       */
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
	int	pipe[2][2];
	int	*pid;
	//int		fd_in;
	//int		fd_out;
}				t_pipe;

/// @brief the redirection struct
typedef struct s_redirection
{
	int						fd;
	e_token_type			type;
	char					*file_name;
	char					*limiter;
	struct s_redirection	*next;	//TYPE LIST
}	t_redirection;

/// @brief 
typedef struct s_cmd
{
	char			*cmd_str;
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
	t_list		*env;
	t_cmd		**cmds;
	t_token		**tokens;
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
/*									ENVIROMENT								  */
/* ************************************************************************** */
t_list			*env_init(char **envp);
char			**env_to_str(t_list *env);
int				is_valid_env(const char *var);
int				is_in_env(t_list *env, char *args);
char			*get_env_name(char *dest, const char *src);
void			print_env(t_list *env, bool export);

/* ************************************************************************** */
/*									REDIRECTION								  */
/* ************************************************************************** */
t_redirection	*redir_new(int fd, e_token_type type, char *file_name, char *limiter);
t_redirection	*redir_last(t_redirection *redir);
void			redir_add_back(t_redirection **redir, t_redirection *new);
void			redir_add_front(t_redirection **redir, t_redirection *new);
void			redir_clear(t_redirection **redir);
void			check_redirections(t_cmd **cmds);
void			check_type(t_redirection *redir);
bool			get_input(t_redirection *redir, bool heredoc);
bool			set_output(t_redirection *redir, bool append);

/* ************************************************************************** */
/*									EXPANSION								  */
/* ************************************************************************** */
t_token			**check_expandable_var(t_token **tokens, t_list *env);

/* ************************************************************************** */
/*									PATH									  */
/* ************************************************************************** */
char			**set_path(char **envp, t_data *data);

/* ************************************************************************** */
/*									BUILTINS								  */
/* ************************************************************************** */
int				ft_cd(t_cmd *cmd, t_list *env);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_list *env);
int				ft_export(t_list *args, t_list *env);
int				ft_pwd(void);
int				ft_unset(t_list *args, t_list *env);

/* ************************************************************************** */
/*									EXECUTION								  */
/* ************************************************************************** */
void			execute_cmds(t_data *data);
int				is_builtin(char *command);
int				exec_builtin(t_cmd *cmd, t_data *data);

/* ************************************************************************** */
/*									DEBUG									  */
/* ************************************************************************** */
void			print_data(t_data *data);

/* ************************************************************************** */
/*								Error Handling								  */
/* ************************************************************************** */
int				print_error(int error, const char *arg);
void			free_data(t_data *data);


//Creating a tree, where the left branch will be executed first.
#endif