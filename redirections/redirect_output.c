/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:49:57 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/23 16:49:30 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	redirect_file_output(t_cmd *cmd)
{
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (false);
	close(cmd->fd_out);
	return (true);
}

bool	redirect_pipe_output(t_pipe *pipe, int j)
{
	if (dup2(pipe->fd[j][1], STDOUT_FILENO) == -1)
		return (false);
	close(pipe->fd[j][1]);
	return (true);
}

bool	redirect_stdout(t_data *data, t_cmd *cmd)
{
	cmd->fd_out = data->origin_fds[1];
	if (dup2(data->origin_fds[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("failed at input\n", 1);
		return (false);
	}
	close(cmd->fd_out);
	return (true);
}
