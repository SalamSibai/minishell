/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/03 18:06:52 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

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
	int				fd;
	e_token_type	type;
	char			*file_name;
	char			*limiter;
}	t_redirection;

/// @brief 
typedef struct s_cmd
{
	char			*cmd_str;
	char			*args_str;
	t_redirection	*redirection;
}	t_cmd;

/// @brief Stores information on tokens
typedef struct s_token
{
	char			*token_string;
	e_token_type	type;
}				t_token;


//Not sure what this is for yet
typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}				t_env;

typedef struct s_lexer
{
	int	n_cmds;
	int	n_pipes;
	int	n_redirections;
	int	n_tokens;
}	t_lexer;


//typedef	struct s_abstract_syntax_tree
//{
//	t_cmd	*cmd;
//	t_token	*root;
//	t_ast *left_branch;
//	t_ast *right_branch;
//
//}		t_ast;

/*
* 	Data struct, containing references to all other structs, whcih includes:
* 	1) a matrix of all the commands that exist, with all the information needed for each command
* 
* 	Things that can be potentially added:
* 	1) A split version of the "PATH" variable, to have an easy access to each directory
* 	2) The env variable that is sent from main, stored for easy access
*/

typedef struct s_data
{
	int			cmd_num;
	t_list		*env;
	t_cmd		**cmds; 	//if each command has a seaprate entry in its own struct, it is not necessary to have a double pointer of cmds in the struct itself
						//or, we can store all commands in that single struct, with it having a double pointer.
	t_token		**tokens;
	char		**env_var;
	char		**path;
	char		*buf;
//	t_pipe		(*)pipe;
//	t_redirect	(*)redirect;
}				t_data;


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
void			init_redirections(t_redirection *redir);
void			init_cmd(t_cmd *cmd);
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

/* ************************************************************************** */
/*									EXPANSION								  */
/* ************************************************************************** */
t_token			**check_expandable_var(t_token **tokens, t_list *env);

/* ************************************************************************** */
/*									PATH									  */
/* ************************************************************************** */
char			**set_path(char **envp, t_data *data);


/* ************************************************************************** */
/*									DEBUG									  */
/* ************************************************************************** */
void			print_data(t_data *data);

//Creating a tree, where the left branch will be executed first.
#endif