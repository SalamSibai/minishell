/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/21 17:52:52 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 */
int	exec_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
	/*
		WE MUST FORK FIRST AND IN THE CHILD WE REDIRECT AND EXECUTE
	*/
	int	pid;

	pid = fork();
	// if (pid == -1)
	// 	error_handler(FORK_ERR, 1, d, p);
	if (pid == 0)
	{
		if (!redirect_fds(data, cmd, i, j))
			ft_putstr_fd("\n redirect failed\n", 1);
		if (is_builtin(cmd->cmd_str))
		{
			if (is_env_builtin(cmd->cmd_str))
			{
				exit (2);
			}
			exec_builtin(cmd, data);
			close_fds(data, i);
			exit(2);
		} 
		else
		{
			if (!get_path(data, cmd))
				ft_putstr_fd("failed to find path for the command\n", 1); //free and cleanup
			close_fds(data, i);
			if (cmd->flag)
			{
				if (join_cmd_and_flag(cmd))
					execve(cmd->cmd_path, cmd->cmd_with_flag, data->env);
				//else exit (failed)
			}
			else
				execve(cmd->cmd_path, cmd->cmd_str, data->env);
		}
	}
	else
	{
		//global variable status
		waitpid(pid, 0, 0);
		if (is_env_builtin(cmd->cmd_str))
		{
			exec_builtin(cmd, data);
			// close_fds(data, i);
		}
			
		// close_fds(data, i);
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

	i = 0;
	j = 0;
	alloc_pids(data);
	if (!make_pipes(data->pipe))
		ft_putstr_fd("ERROR WITH MAKING PIPES\n", 1);
	if (data->cmd_num > 1)
	{
		while (data->cmds[i] != NULL && data->cmds[i]->cmd_str != NULL)
		{
			data->pipe->pid[i] = exec_cmd(data->cmds[i], data, i, j);
			if (i >= 1 && i < data->cmd_num - 1)
			{
				close_fds(data, i);
				if (pipe(data->pipe->fd[!j] == -1))
					ft_putstr_fd("ERROR WITH MAKING PIPES\n", 1);
			}
			i++;
			j = !j;
		}
	}
	else
		exec_cmd(data->cmds[0], data, 0 , 0);
}
