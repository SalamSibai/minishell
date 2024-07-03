/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:25:27 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/03 19:14:36 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	make_pipes(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pipe(p->fd[i]) == -1)
			return (false);
		i ++;
	}
	return (close_pipe(data->pipe));
}

void	alloc_pids(t_data *data)
{
	data->pipe->pid = (int *)malloc(data->cmd_num * sizeof(int));
	if (!data->pipe->pid)
		return ;
}