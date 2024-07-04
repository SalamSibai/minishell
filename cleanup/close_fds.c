/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:25:27 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/03 19:19:31 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	close_everything()
{
	int i;

	i = 0;
	while (i < 1025)
	{
		close(i);
		i ++;
	}
	return (true);
}

bool	close_fd(int fd)
{
	if (close(fd) == -1)
		return (false);
	return (true);
}

void	close_origin_fds(t_data *data)
{
	close(data->origin_fds[0]);
	close(data->origin_fds[1]);
}

bool	close_pipe(t_pipe *pipe, int i, bool both)
{
	int	j;

	j = -1;
	if (both)
	{
		i = -1;
		while (++i < 2)
		{
			j = -1;
			while (++j < 2)
			{
				{
					if (close(pipe->fd[i][j]) == -1)
						return (false);
				}
			}
		}
	}
	else
	{
		while (++j < 2)
		{
			{
				if (close(pipe->fd[i][j]) == -1)
					return (false);
			}
		}
	}
	return (true);
}

bool	close_fds(t_data *data, int i, bool pipe)
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
		if (close(data->cmds[i]->fd_out) == -1)
			return (false);
	}
	if (pipe)
	{
		if (!close_pipe(data->pipe, j, true))
			return (false);
	}
	return (true);
}
