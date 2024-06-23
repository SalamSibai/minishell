/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:35:28 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/23 23:39:48 by mohammoh         ###   ########.fr       */
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
	return (true);
}

void	alloc_pids(t_data *data)
{
	data->pipe->pid = (int *)malloc(data->cmd_num * sizeof(int));
	if (!data->pipe->pid)
		return ;
}