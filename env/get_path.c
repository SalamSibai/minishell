/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:00:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/30 22:10:16 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_path(char **envp, t_data *data)
{
	char	*full_path;
	char	**split_path;
	char	*tmp;
	int		i;

	(void)data;
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

	//if (full_path == NULL)
	//CODE
	// else
	split_path = ft_split(full_path, ':');
	while (split_path[++i] != NULL)
	{
		tmp = ft_strdup(split_path[i]);
		free(split_path[i]);
		split_path[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
	return (split_path);
}
