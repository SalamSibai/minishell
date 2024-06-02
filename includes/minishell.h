/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/02 20:08:08 by ssibai           ###   ########.fr       */
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
	CMDS,
	PIPE,
	LIMITER,
	FILE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	REDIRECT_APPEND,
	FLAG,
	ID,
	DQOUTES,
	SQOUTES
	//SEMICOLON,
	//NEWLINE,
	//END
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

/// @brief 
typedef struct s_redirection
{
	int				fd;
	e_token_type	type;
	char			*file_name;
}	t_redirection;

/// @brief 
typedef struct s_args
{
	char			*arg_str;
	t_redirection	*redirection;
}	t_args;

/// @brief 
typedef struct s_cmd
{
	char	*cmd_str;
	t_args	*args;
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
	t_list		*env;
	t_cmd		**cmd; 	//if each command has a seaprate entry in its own struct, it is not necessary to have a double pointer of cmds in the struct itself
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

bool	validate_syntax(char *line);
bool	validate_unbalanced_qoutes(char *line);
bool	validate_pipes(char *line);
bool	validate_id(t_parsing *parse, int index);
bool	validate_pipe(t_parsing *parse, int index);
bool	validate_input_redirection(t_parsing *parse, int index);
bool	validate_output_redirection(t_parsing *parse, int index);

/* ************************************************************************** */
/*									PARSEING								  */
/* ************************************************************************** */
bool			pasre_setup(t_parsing *parse, int token_ctr);
void			scan(char *av, t_parsing *parse);


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


/* ************************************************************************** */
/*									ENVIROMENT								  */
/* ************************************************************************** */
t_list			*env_init(char **envp);
char			**env_to_str(t_list *env);


/* ************************************************************************** */
/*									PATH									  */
/* ************************************************************************** */
char			**set_path(char **envp, t_data *data);


//Creating a tree, where the left branch will be executed first.
#endif