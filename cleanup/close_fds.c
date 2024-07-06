/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:25:27 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/05 05:42:05 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_everything(void)
{
	int	i;

	i = 3;
	while (i < 64)
	{
		(void) close(i);
		i++;
	}
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
				if (close(pipe->fd[i][j]) == -1)
					return (false);
			}
		}
	}
	else
	{
		while (++j < 2)
		{
			if (close(pipe->fd[i][j]) == -1)
				return (false);
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
