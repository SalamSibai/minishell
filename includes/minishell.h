/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/22 18:31:42 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_token_type
{
	COMMAND,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	REDIRECT_APPEND,
	FLAG,
	ID
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
//	t_pipe		(*)pipe;
//	t_redirect	(*)redirect;
}				t_data;

/* ************************************************************************** */
/*									PARSE UTILS								  */
/* ************************************************************************** */

int		ft_panic(char *message, int ret);
void	*ft_safe_malloc(size_t size);

//Creating a tree, where the left branch will be executed first.

#endif