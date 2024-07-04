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
		i = 0;
		while (i < 2)
		{
			j = -1;
			while (++j < 2)
			{
				{
					if (close(pipe->fd[i][j]) == -1)
					{
						printf("closing pipe %d failed\n", i);
						return (false);
					}
				}
			}
			i ++;
		}
		return (true);
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
		return (true);
	}
	return (false);
}

bool	close_fds(t_data *data, int i, bool pipe)
{
	int	j;

	j = 0;
	if (data->cmds[i]->fd_in != -1)
	{
		printf("the fd is : %d\n",data->cmds[i]->fd_in);
		if (close(data->cmds[i]->fd_in) == -1)
		{
			printf("CLOSING FAILED at input\n");
			return (false);
		}
		data->cmds[i]->fd_in = -1;
	}
	if (data->cmds[i]->fd_out != -1)
	{
		if (close(data->cmds[i]->fd_out) == -1)
		{
			printf("CLOSING FAILED at output\n");
			return (false);
		}
		data->cmds[i]->fd_out = -1;
	}
	if (pipe)
	{
		printf("PIPE IS TRUE\n");
		printf("the command is %s\n", data->cmds[i]->cmd_str);
		if (!close_pipe(data->pipe, j, true))
		{
			printf("pipe closing failed\n");
			return (false);
		}
	}
	return (true);
}
