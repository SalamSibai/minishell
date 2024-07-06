/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:41:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/06 14:59:12 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 */
bool	set_output(t_cmd *cmd, bool append, t_redirection *redir)
{
	char	*file_path;

	if (cmd->fd_out != -1)
	{
		if (!close_fd(cmd->fd_out))
			return (false);
	}
	if (!append)
	{
		cmd->fd_out = open(redir->file_name,
				O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (!cmd->fd_out)
			return (false);
	}
	else
	{
		cmd->fd_out =  open(redir->file_name,
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (!cmd->fd_out)
			return (false);
	}

	file_path = get_file_path(redir->file_name);
	if (access(file_path, W_OK) != 0)
	{
		free(file_path);
		close_fd(cmd->fd_out);
		cmd->fd_out = -1;
		return (false);
	}
	free(file_path);
	return (true);
}
