/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/02 19:24:31 by ssibai           ###   ########.fr       */
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
	CMDS,						// 1
	PIPE,						// 2
	LIMITER,					//3
	FILE_NAME,  				//4
	REDIRECT_INPUT,				//5
	REDIRECT_OUTPUT,			//6
	HEREDOC,					//7
	REDIRECT_APPEND,			//8
	FLAG,						//9
	ID,							//10
	EXEC_ID,					//11
	DQOUTES,					//12
	SQOUTES						//13
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

/*
*	stores the information of each command which includes:
*	1)	where it reads from and where its reading to
*	2) 	the path that stores the executable (if any, or if its a builtin)
* 	3)	the command itself
* 
* 	things that can be added:
* 	2) a serial number for each command
*/ 
typedef struct s_cmd
{
	char	*cmd;
	char	*path;
	int		cmd_sn;
//	int		pipe; maybe the pipe fd to read from? 0 and 1 being pipes
	int		fd_in;
	int		fd_out;
}				t_cmd;

/*
* 	Stores information on tokens
* */
typedef struct s_token
{
	char			*token_string;
	e_token_type	type;
}				t_token;

/*
*	Redirect struct, includes: 
*	1) the value of the fd (COULD ALSO BE A REFERENCE TO THE PIPE'S FD)
*	2) the type (1 for inputfile, 2 for outputfile, 3 for stdin, 4 for stdout, can be stored in an enum)
* 	3) if its a file, the name of the file.
* */
typedef struct s_redirect
{
	int		fd;
	int		type;
	char	*file;
}				t_redirect;

//Not sure what this is for yet
typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}				t_env;

/*
* 	The initial scan of the input, which can include:
* 	1) number of commands
* 	2) 
* */
typedef struct s_lexer
{
	int		n_cmds;
	int		n_pipes;
	int		n_redirects;
	int		n_token;
//	int		n_semicolons;
//	int		n_newlines;
}				t_lexer;

typedef	struct s_parsing
{
	t_token **tokens;
	t_lexer	*lexer;
}		t_parsing;

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
	t_parsing	*parse_data;
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
bool			validate_tokens(t_parsing *parse, t_data *data);
bool			validate_pipes(char *line);
bool			validate_id(t_parsing *parse, int index, t_data *data);
bool			validate_pipe(t_parsing *parse, int index);
bool			validate_input_redirection(t_parsing *parse, int index);
bool			validate_output_redirection(t_parsing *parse, int index);
bool			validate_qoutes(t_parsing *parse, int index, t_data *data);

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