/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 22:36:17 by mohammoh         ###   ########.fr       */
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
# include <sys/stat.h>

# define BUFF_SIZE 4096
# define INVALID_EXP_MSG "Export: not a valid identifier\n"
# define INVALID_IN_MSG "Error: Invalid syntax\n"
# define INPUT_REDIR_ER_MSG "Error: No such file or directory\n"
# define OUTPUT_REDIR_ER_MSG "Error: Output redirection error\n"
# define TOO_MANY_ARG "Error: too many arguments\n"
# define NUMERIC_REQ_MSG "Error: Numeric argument required\n"
# define PATH_ER_MSG "Error: Path doesnt exists\n"
# define PIPE_ER_MSG "Error: Couldn't open pipes\n"
# define FORK_ER_MSG "Error: Fork.\n"
# define CMD_ER_MSG "Error: Command doesn't exits\n"
# define DIR_MSG "Error: No such file or directory\n"
# define PIPE_MISSING "Error: syntax error near unexpected token '|'\n"

typedef enum e_cmd_type
{
	SET,
	FREE,
}	t_cmd_type;

typedef enum e_error_type
{
	NUM_REQ_ER,
	INVALID_IN_ER,
	IN_REDIR_ER,
	OUT_REDIR_ER,
	PATH_ER,
	PIPE_ER,
	FORK_ER,
	DIR_EXEC_ER,
	CMD_ER
}	t_error_type;

typedef struct sigaction	t_sigaction;

int							g_recived_signal;

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

typedef struct s_var
{
	int				i;
	int				j;
	int				len;
	int				tkn_ctr;
	int				c;
	int				x;
	int				k;
	t_token_type	type;
	bool			expandable;

}	t_var;

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
	bool		duped;
	int			g_exit_status;
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
int				if_id(t_data *data, int i, t_token **tokens);
int				if_pipe(t_data *data, int i, t_token **tokens);
int				if_input(int i, t_token **tokens);
int				if_output(int i, t_token **tokens);
int				if_quote_or_dquote(int i, t_token **tokens, t_data *data);

/* ************************************************************************** */
/*									SIGNALS									  */
/* ************************************************************************** */
void			init_sigaction(t_data *data);
void			disable_ctrl_c_echo(void);

/* ************************************************************************** */
/*									PARSEING								  */
/* ************************************************************************** */
void			scan(char *av, t_token **tokens);
void			init_cmds(t_data *data);
void			set_cmds(t_data *data);
int				count_cmds(t_token **tokens);
void			malloc_each_token(t_var *var, t_token **tokens, char *buff);
void			malloc_qoutes_token(t_token **tokens, char *buff, t_var *var);
bool			check_if_cmd(t_data *data, t_var *var, t_token **tokens);
bool			check_if_flag(t_data *d, t_var *v, t_token **ts, t_list *n);
bool			check_if_redir(t_var *var, t_token **tokens,
					t_redirection **head);
bool			check_if_id(t_data *data, t_var *var, t_token **tokens,
					t_list *new_arg);
void			itir_tokens(int *token_ctr, int *in_t, char *av, int *i);

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
bool			is_dquote_or_quote(int *tkn_ctr, int *in_t, char *av, int *i);
bool			is_append_or_heredoc(int *tn_ctr, int *in_t, char *av, int *i);
bool			is_pipe_or_redir(int *tkn_ctr, int *in_tokn, char *av, int i);
int				skip_spaces(int *token_ctr, int *in_token, char *av, int i);

/* ************************************************************************** */
/*								REDIRECTION	UTILS							  */
/* ************************************************************************** */
t_redirection	*redir_new(t_token_type type, char *file_name, char *limiter);
t_redirection	*redir_last(t_redirection *redir);
void			redir_add_back(t_redirection **redir, t_redirection *new);
void			redir_add_front(t_redirection **redir, t_redirection *new);
void			redir_clear(t_redirection **redir);
void			reset_fds(t_data *data);

/* ************************************************************************** */
/*								PIPES,FDs REDIRECTION		 				  */
/* ************************************************************************** */
void			check_redirections(t_cmd *cmd, t_data *data,
					int *in_val, int *out_val);
bool			get_input(t_cmd *cmd, bool heredoc, t_redirection *redir,
					t_data *data);
bool			set_output(t_cmd *cmd, bool append, t_redirection *redir);
bool			redirect_fds(t_data *data, t_cmd *cmd, int i, int j);
bool			redirect_file_input(t_cmd *cmd);
bool			redirect_pipe_input(t_pipe *pipe, int j);
bool			redirect_file_output(t_cmd *cmd);
bool			redirect_pipe_output(t_pipe *pipe, int j);
bool			redirect_stdin(t_data *data, t_cmd *cmd);
bool			redirect_stdout(t_data *data, t_cmd *cmd);
char			*get_file_path(const char *file_name);
void			alloc_pids(t_data *d);
bool			make_pipes(t_pipe *p);

/* ************************************************************************** */
/*									EXPANSION								  */
/* ************************************************************************** */
t_token			**check_expandable_var(t_token **tokens, t_data *data);
char			*replace_env_var(char *str, t_list *env, t_data *data);

/* ************************************************************************** */
/*									PATH									  */
/* ************************************************************************** */
char			**set_path(char **envp);
bool			get_path(t_data *data, t_cmd *cmd, bool *cmd_exists);

/* ************************************************************************** */
/*									ENVIROMENT								  */
/* ************************************************************************** */
t_list			*env_init(char **envp);
t_list			*export_env_init(t_list *env);
char			**env_to_str(t_list *env);
void			ft_export_pwds(char *str, t_list *export_env,
					t_list *env);
bool			is_valid_env(const char *var);
char			*add_quotes(char *value);
bool			is_in_env(t_list *env, char *args);
char			*get_env_name(char *dest, const char *src);
void			print_env(t_list *env, bool export);
int				env_add(char *value, t_list *env);
bool			print_error(const char *arg);
bool			set_env_and_path(t_data *data, t_cmd_type type);
void			bubble_sort(t_list *head,
					int (*cmp)(const char *, const char *));

/* ************************************************************************** */
/*									BUILTINS								  */
/* ************************************************************************** */
int				ft_cd(t_cmd *cmd, t_list *env, t_list *exp_env, t_data *data);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_list *env);
bool			ft_export(t_cmd *cmd, t_list *export_env, t_list *env);
int				ft_pwd(void);
int				ft_unset(t_list *args, t_list *env, t_data *data);
int				ft_exit(t_cmd *cmd, t_data *data);

/* ************************************************************************** */
/*									EXECUTION								  */
/* ************************************************************************** */
bool			is_builtin(char *command);
bool			is_env_builtin(char *command);
int				exec_builtin(t_cmd *cmd, t_data *data);
bool			execution(t_data *data);
bool			join_cmd_and_flag(t_cmd *cmd);
bool			is_directory(const char *path);
bool			set_redir(t_cmd *cmd, t_data *data);
void			dup_origin(t_data *data);
bool			exec_redir(t_data *data, t_cmd *cmd, int i, int j);
int				check_builtin(t_cmd *cmd, t_data *data);
bool			check_env_builtin(t_cmd *cmd, t_data *data);
void			processes_queue(t_data *data, int *status);
bool			exec_multiple(t_data *data, int i);
int				exec_cmd(t_cmd *cmd, t_data *data, int i, int j);
void			exec_in_v(t_cmd *cmd, t_data *data, int i, bool *cmd_exist);

/* ************************************************************************** */
/*									DEBUG									  */
/* ************************************************************************** */
void			print_data(t_data *data);

/* ************************************************************************** */
/*								Error Handling								  */
/* ************************************************************************** */
void			error_handler(char *err_str, int err_type,
					t_data *data, bool done);
void			free_cmd(t_data *data);
void			free_tokens(t_data *data);
void			cleanup(t_data *data);
bool			close_fd(int fd);
bool			close_fds(t_data *data, int i, bool pipe);
bool			close_pipe(t_pipe *pipe, int i, bool both);
void			close_origin_fds(t_data *data);
void			close_all_fds(int start);

#endif