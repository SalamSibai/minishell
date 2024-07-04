/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:00:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/04 06:29:29 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_path(char **envp)
{
	char	*full_path;
	char	**split_path;
	char	*tmp;
	int		i;

	i = -1;
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
