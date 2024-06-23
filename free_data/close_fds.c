/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:25:27 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/22 16:48:15 by ssibai           ###   ########.fr       */
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
	while (j < 2)
	{
		if (pipe->fd[i][j] != -1 && close(pipe->fd[i][j]) == -1)
			ft_putstr_fd("error closing pipe.\n", 1);
		j ++;
	}
	return (true);
}

bool	close_pipes(t_pipe *pipe)
{
	int	i;
	int	j;

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
	return (true);
}

bool	close_fds(t_data *data, int i)
{
	// if (data->cmds[i]->fd_in != -1)
	// {
	if (close(data->cmds[i]->fd_in) == -1)
		return (false);
	// }
	// else
	// {
	// 	data->cmds[i]->
	// }
	// if (data->cmds[i]->fd_out != -1)
	// {
	if (close(data->cmds[i]->fd_out == -1))
		return (false);
	// }
	return (close_pipes(data->pipe));
}
