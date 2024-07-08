/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:06:31 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 17:56:08 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function will execute the commands based on the type of command
 * either its a builtin or a command to be executed in the parent or the child
 * @param data 
 */
void	execute_single_cmd(t_data *data)
{
	if (is_builtin(data->cmds[0]->cmd_str))
		data->g_exit_status = exec_builtin(data->cmds[0], data);
	else
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
}
/**
 * @brief this function will execute the commands based on the type of command
 * 	SHOULD MAKE FUNCTION BOOL?
 * @param data
 */
bool	execution(t_data *data)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	alloc_pids(data);
	if (data->cmd_num > 1)
	{
		if (!exec_multiple(data, i))
			return (false);
	}
	else
		execute_single_cmd(data);

	i = -1;
	if (data->duped)
		reset_fds(data);
	if (data->cmd_num > 1)
		processes_queue(data, &status);
	else if (data->cmds[0]->cmd_str && !is_builtin(data->cmds[0]->cmd_str)
		&& data->pipe->pid[0] != -1)
	{
		waitpid(data->pipe->pid[0], &status, 0);
		data->g_exit_status = WEXITSTATUS(status);
	}
	return (true);
}
