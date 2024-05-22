/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:00:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/08 17:25:24 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//this function will return the node to be used by export and unset

/*char	**get_path(char **env_str)
{
	char	**paths;
	char	*path;
	int		i;
	int		j;

	i = -1;
	while (env_str[++i])
	{
		if (ft_strncmp(env_str[i], "PATH=", 5) == 0)
			path = ft_strdup(env_str[i]);
	}
	i = -1;
	j = 0;
	while (path[++i])
	{
		if (path[i] == ':')
			j++;
	}
	paths = ft_safe_malloc(sizeof(char *) * (j + 2), "PATHS");
	i = -1;
	j = 0;
	while (path[++i])
	{
		
	
	}
}*/


void	set_path(char **envp, t_data *data)
{
	char	*full_path;
    char    **split_path;
    int     i;

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
        data->path = ft_strjoin(split_path[i], '/');
    }
	ft_free2d(split_path);
}
