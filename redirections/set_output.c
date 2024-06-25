/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:41:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/25 20:46:36 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	set_output(t_cmd *cmd, bool append, t_redirection *redir)
{
	char	 *path;
	char	*file_path;
	char	cwd[PATH_MAX];

	if (cmd->fd_out != -1)
	{
		if (!close_fd(cmd->fd_out))
			return (false);
	}
	path = getcwd(cwd, PATH_MAX);
	file_path = ft_strjoin(path, "/");
	file_path = ft_strjoin(file_path, redir->file_name);
	if (access(file_path, X_OK) != 0)
	{
		printf("access denied\n");
		return (free(file_path), false);
	}
	if (!append)
	{
		cmd->fd_out = open(redir->file_name,
				O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (!cmd->fd_out)
			return (free(file_path), false);
	}
	else
	{
		cmd->fd_out =  open(redir->file_name,
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (!cmd->fd_out)
			return (free(file_path), false);
	}
	return (free(file_path), true);
}
