/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:49:57 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/22 14:02:37 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	redirect_file_output(t_cmd *cmd)
{
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (false);
	return (true);
}

bool	redirect_pipe_output(t_pipe *pipe, int j)
{
	if (dup2(pipe->fd[j][0], STDOUT_FILENO) == -1)
		return (false);
	return (true);
}

bool	redirect_stdout(t_data *data, t_cmd *cmd)
{
	cmd->fd_out = dup(STDOUT_FILENO);
	if (cmd->fd_out == -1)
	{
		ft_putstr_fd("still -1\n", 1);
		return (false);
	}
	data->origin_fds[0] = dup(STDOUT_FILENO);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("failed at input\n", 1);
		return (false);
	}
	return (true);
}
