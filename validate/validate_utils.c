/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:47:04 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 22:36:51 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function will return if the searched token is found in the string
 * 
 * @param ps a double pointer that points to the string
 * @param es a pointer that potins to the end of the string
 * @param token the token we are looking for
 * @return return 1 if the token is found, 0 if not
 */
int	ft_peek(char **ps, char *es, char *token)
{
	char	*s;

	s = *ps;
	while (s < es && ft_isspace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(token, *s));
}

bool	validate_unbalanced_qoutes(char *line)
{
	int		i;
	char	qoute;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			qoute = line[i];
			i++;
			while (line[i] && line[i] != qoute)
				i++;
			if (!line[i])
			{
				printf("Error: unmatched qoutes\n");
				return (false);
			}
			i++;
		}
		else
			i++;
	}
	return (true);
}

bool	find_pipe(char *ps, char *es)
{
	if (ft_peek(&ps, es, "|"))
	{
		printf(PIPE_MISSING);
		return (false);
	}
	return (true);
}

bool	validate_pipes(char *line)
{
	char	*ps;
	char	*es;

	ps = line;
	es = line + ft_strlen(line);
	while (ps < es && ft_isspace(*ps))
		ps++;
	if (!find_pipe(ps, es))
		return (false);
	while (ps < es)
	{
		if (*ps == '|')
		{
			ps++;
			while (ps < es && ft_isspace(*ps))
				ps++;
			if (ps == es || *ps == '|')
				return (printf(PIPE_MISSING), false);
		}
		else
			ps++;
	}
	return (true);
}

/// @brief checks whether the ID sent is a command
bool	is_cmd(char *cmd, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (data->path[i] != NULL)
	{
		cmd_path = ft_strjoin(data->path[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (free(cmd_path), true);
		free(cmd_path);
		i++;
	}
	return (false);
}
