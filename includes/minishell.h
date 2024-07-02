/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/02 21:47:59 by ssibai           ###   ########.fr       */
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
# include <signal.h>

# define BUFF_SIZE 4096
# define INVALID_IN_MSG "Error: Invalid input\n"
# define INPUT_REDIR_ER_MSG "Error: Input redirection error.\n"
# define OUTPUT_REDIR_ER_MSG "Error: Output redirection error.\n"
# define PATH_ER_MSG "Error: Path doesn't exist\n"
# define PIPE_ER_MSG "Error: Couldn't opern pipes.\n"
# define FORK_ER_MSG "Error: Fork.\n"
# define CMD_ER_MSG "Error: Command doesn't exits.\n"

typedef enum e_error_type
{
	INVALID_IN_ER,
	IN_REDIR_ER,
	OUT_REDIR_ER,
	PATH_ER,
	PIPE_ER,
	FORK_ER,
	CMD_ER
} e_error_type;

typedef struct sigaction	t_sigaction;

int							g_exit_status;

typedef enum t_token_type
{
	CMDS,
	PIPE,
	LIMITER,
	FILE_NAME,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	REDIRECT_APPEND,
	REDIR_INPUT_FAILED,
	REDIR_OUTPUT_FAILDED,
	FLAG,
	ID,
	EXEC_ID,
	DQOUTES,
	SQOUTES,
	NONE
}	t_token_type;

/**
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
	t_token_type			type;
	char					*file_name;
	char					*limiter;
	struct s_redirection	*next;
}	t_redirection;

/// @brief 
typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			*cmd_path;
	char			*cmd_str;
	char			**cmd_with_flag;
	t_list			*flag;
	t_list			*args;
	t_redirection	*redirection;
}	t_cmd;

/// @brief Stores information on tokens
typedef struct s_token
{
	char			*token_string;
	t_token_type	type;
	bool			expandable;
}				t_token;

/**
 * @brief this structure contains all the data
 * thatll be used in our minishell
 */
typedef struct s_data
{
	t_token		**tokens;
	t_list		*env;
	t_list		*export_env;
	t_cmd		**cmds;
	t_pipe		*pipe;
	char		**env_var;
	char		**path;
	char		*buf;
	int			cmd_num;
	int			cmd_ctr;
	int			origin_fds[2];
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
/*									SIGNALS									  */
/* ************************************************************************** */
void			init_sigaction(void);
void			disable_ctrl_c_echo(void);

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
/*								REDIRECTION	UTILS							  */
/* ************************************************************************** */
t_redirection	*redir_new(t_token_type type, char *file_name, char *limiter);
t_redirection	*redir_last(t_redirection *redir);
void			redir_add_back(t_redirection **redir, t_redirection *new);
void			redir_add_front(t_redirection **redir, t_redirection *new);
void			redir_clear(t_redirection **redir);

/* ************************************************************************** */
/*								PIPES,FDs REDIRECTION		 				  */
/* ************************************************************************** */
int				check_redirections(t_cmd **cmds);
int				check_type(t_cmd *cmd);
bool			get_input(t_cmd *cmd, bool heredoc, t_redirection *redir);
bool			set_output(t_cmd *cmd, bool append, t_redirection *redir);
bool			redirect_fds(t_data *data, t_cmd *cmd, int i, int j);
bool			redirect_file_input(t_cmd *cmd);
bool			redirect_pipe_input(t_pipe *pipe, int j);
bool			redirect_file_output(t_cmd *cmd);
bool			redirect_pipe_output(t_pipe *pipe, int j);
bool			redirect_stdin(t_data *data, t_cmd *cmd);
bool			redirect_stdout(t_data *data, t_cmd *cmd);
bool			close_pipe(t_pipe *pipe, int i);
void			alloc_pids(t_data *d);
bool			make_pipes(t_pipe *p);

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
void			print_env(t_list *env, bool export);
bool			print_error(const char *arg);
void			bubble_sort(t_list *head, 
					int (*cmp)(const char *, const char *));

/* ************************************************************************** */
/*									BUILTINS								  */
/* ************************************************************************** */
int				ft_cd(t_cmd *cmd, t_list *env);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_list *env);
bool			ft_export(t_cmd *cmd, t_list *export_env, t_list *env);
int				ft_pwd(void);
int				ft_unset(t_list *args, t_list *env);

/* ************************************************************************** */
/*									EXECUTION								  */
/* ************************************************************************** */
bool			is_builtin(char *command);
bool			is_env_builtin(char *command);
int				exec_builtin(t_cmd *cmd, t_data *data);
void			execute_cmds(t_data *data);
bool			execution(t_data *data);
bool			join_cmd_and_flag(t_cmd *cmd);

/* ************************************************************************** */
/*									DEBUG									  */
/* ************************************************************************** */
void			print_data(t_data *data);

/* ************************************************************************** */
/*								Error Handling								  */
/* ************************************************************************** */
void	 error_handler(char *err_str, int err_type, t_data *data, bool done);
void	free_data(t_data *data, bool done);
void	cleanup(t_data *data);
bool	close_fd(int fd);
bool	close_fds(t_data *data, int i);
bool	close_pipe(t_pipe *pipe, int i);
void	close_origin_fds(t_data *data);

#endif