/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:25:27 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/23 17:31:31 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	close_fd(int fd)
{
	if (close(fd) == -1)
		return (false);
	return (true);
}

bool	close_pipe(t_pipe *pipe, int i)
{
	int	j;

	j = 0;
	while (++j < 2)
	{
		{
			if (close(pipe->fd[i][j]) == -1)
				return (false);
		}
	}
	return (true);
}

bool	close_fds(t_data *data, int i)
{
	int	j;

	j = 0;
	if (data->cmds[i]->fd_in != -1)
	{
		if (close(data->cmds[i]->fd_in) == -1)
			return (false);
	}
	if (data->cmds[i]->fd_out != -1)
	{
		if (close(data->cmds[i]->fd_out == -1))
			return (false);
	}
	while (j < 2)
	{
		if (!close_pipe(data->pipe, i))
			return (false);
		j ++;
	}
	return (true);
}
