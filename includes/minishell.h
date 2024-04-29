/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:17:44 by mohammoh          #+#    #+#             */
/*   Updated: 2024/04/29 19:24:00 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_pipe
{
	int		pipe[2][2];
	int		fd_in;
	int		fd_out;
}				t_pipe;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	int		pipe;
	int		fd_in;
	int		fd_out;
}				t_cmd;

typedef struct s_token
{
	char	*token;
	int		type;
}				t_token;

typedef struct s_redirect
{
	int		fd;
	int		type;
	char	*file;
}				t_redirect;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	t_env	*env;
	t_cmd	*cmd;
	t_pipe	pipe;
	t_redirect	redirect;
}				t_data;
#endif