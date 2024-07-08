/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:08:31 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 21:08:34 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_fds(t_data *data)
{
	dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	close_origin_fds(data);
	close_all_fds(3);
}

char	*get_file_path(const char *file_name)
{
	char	*path;
	char	*file_path1;
	char	*file_path;
	char	cwd[PATH_MAX];

	path = getcwd(cwd, PATH_MAX);
	if (!path)
		return (NULL);
	file_path1 = ft_strjoin(path, "/");
	if (!file_path1)
		return (NULL);
	file_path = ft_strjoin(file_path1, file_name);
	ft_free(&file_path1, 'p');
	return (file_path);
}
