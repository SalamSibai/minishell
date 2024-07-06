/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:00:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/06 16:00:27 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_full_path(char **envp)
{
	char	*full_path;

	full_path = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH=",*envp, 5) == 0)
		{
			full_path = *envp + 5;
			break ;
		}
		envp ++;
	}
	return (full_path);
}

/**
 * @brief this function will set the path for the shell
 * @param envp is the envp that contains the path
 * @return itll return the path in a double pointer
 */
char	**set_path(char **envp)
{
	char	*full_path;
	char	**split_path;
	char	*tmp;
	int		i;

	i = -1;
	full_path = get_full_path(envp);
	split_path = ft_split(full_path, ':');
	if (!split_path)
		return (NULL);
	while (split_path[++i] != NULL)
	{
		tmp = ft_strdup(split_path[i]);
		free(split_path[i]);
		split_path[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
	return (split_path);
}
