/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/02 20:20:16 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief executes the commands
/// @param cmd pntr to cmd struct
/// @param data pntr to data struct
/// @param i cmd index
/// @param j "flip flop" for pipes
/// @return pid
int	exec_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (error_handler(FORK_ER_MSG, FORK_ER, data, false), pid);
		//ft_putstr_fd("ERROR WITH FORK", 1);
	if (pid == 0)
	{
		data->origin_fds[0] = dup(STDIN_FILENO);
		data->origin_fds[1] = dup(STDOUT_FILENO);
		if (!redirect_fds(data, cmd, i, j))
			return (pid);
		// if (!close_fds(data, i))
		// 	printf("CLOSING PROBLEM\n");
		for (int k = 0; k < data->cmd_num - 1; k++)
		{
			close(data->pipe->fd[k][0]);
			close(data->pipe->fd[k][1]);
		}
		if (is_builtin(cmd->cmd_str) && (data->cmd_num > 1))
		{
			exec_builtin(cmd, data);
			exit(2);
		}
		if (is_env_builtin(cmd->cmd_str))
		{
				free_cmd(data);	
				cleanup(data);
				exit (2);
		}
		else
		{
			if (join_cmd_and_flag(cmd))
			{
				if (get_path(data, cmd))
				{
					execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
				}
				else
					error_handler(PATH_ER_MSG, PATH_ER, data, true);
			}
			else
				error_handler(CMD_ER_MSG, CMD_ER, data, true);
		}
	}
	else
	{
		if (is_env_builtin(cmd->cmd_str) && data->cmd_num == 1)
		{
			pid = getpid();
			if (!redirect_fds(data, cmd, i, j))
				return (pid);
			exec_builtin(cmd, data);
		}
		if (i > 0)
			close(data->pipe->fd[!j][0]);
		if (i < data->cmd_num - 1)
			close(data->pipe->fd[j][1]);
	}
	return (pid);
}

/**
 * @brief this function will execute the commands based on the type of command
 * 	SHOULD MAKE FUNCTION BOOL?
 * @param data
 */
bool	execution(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc_pids(data);
	if (data->cmd_num > 1)
	{
		if (!make_pipes(data->pipe))
			return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
			//return
			//ft_putstr_fd("ERROR WITH MAKING PIPES\n", 1);
		while (data->cmds[i] != NULL)
		{
			data->pipe->pid[i] = exec_cmd(data->cmds[i], data, i, j);
			if (i >= 1 && i < data->cmd_num - 1)
			{
				close_pipe(data->pipe, !j);
				if (pipe(data->pipe->fd[!j]) == -1)
					return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
					//ft_putstr_fd("ERROR WITH MAKING PIPES\n", 1);
				
			}
			i++;
			j = !j;
		}
	}
	else
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0 , 0);
	i = -1;
	while (++i < data->cmd_num)
	{
		waitpid(data->pipe->pid[i],  &g_exit_status, 0);
	}
	dup2(data->origin_fds[0], STDIN_FILENO);
	dup2(data->origin_fds[1], STDOUT_FILENO);
	return (true);
}
