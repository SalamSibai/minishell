/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/23 22:07:22 by ssibai           ###   ########.fr       */
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

	if (!redirect_fds(data, cmd, i, j))
		ft_putstr_fd("\n redirect failed\n", 1);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("ERROR WITH FORK", 1);
	if (pid == 0)
	{
		// if (!redirect_fds(data, cmd, i, j))
		// 	ft_putstr_fd("\n redirect failed\n", 1);
		if (is_builtin(cmd->cmd_str))
		{
			if (is_env_builtin(cmd->cmd_str))
				exit (2);
			//close_fds(data, i);
			exec_builtin(cmd, data);
			exit(2);
		} 
		else
		{
			// if (!redirect_fds(data, cmd, i, j))
			// 	ft_putstr_fd("\n redirect failed\n", 1);
			if (join_cmd_and_flag(cmd))
			{
				if (get_path(data, cmd))
				{
					//close_fds(data, i);
					execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
				}
				else
					ft_putstr_fd("FAILED TO EXECUTE CMD\n", 1);
			}
			else
				ft_putstr_fd("COMMAND NOT FOUND\n", 1);
		}
	}
	else
	{
		//global variable status
		waitpid(pid, 0, 0);
		if (is_env_builtin(cmd->cmd_str))
			exec_builtin(cmd, data);
		//close_fds(data, i);
	}
	return (0);
}

/**
 * @brief this function will execute the commands based on the type of command
 * 
 * @param data
 */
void	execution(t_data *data)
{
	int	i;
	int	j;
	//int	status;

	i = 0;
	j = 0;

	if (data->cmd_num > 1)
	{
		alloc_pids(data);
		if (!make_pipes(data->pipe))
			ft_putstr_fd("ERROR WITH MAKING PIPES\n", 1);
		while (data->cmds[i] != NULL && data->cmds[i]->cmd_str != NULL)
		{
			data->pipe->pid[i] = exec_cmd(data->cmds[i], data, i, j);
			if (i >= 1 && i < data->cmd_num - 1)
			{
				close_pipe(data->pipe, !j);
				if (pipe(data->pipe->fd[!j]) == -1)
					ft_putstr_fd("ERROR WITH MAKING PIPES\n", 1);
			}
			i++;
			j = !j;
		}
	}
	else
		exec_cmd(data->cmds[0], data, 0 , 0);
	i = 0;
	dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	while (i < data->cmd_num)
		close_fds(data, i++);
	//i = 0;
	// while (i < data->cmd_num)
	// {
	// 	waitpid(data->pipe->pid[i++], 0, 0);
	// }
}
