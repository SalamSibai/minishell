/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/21 17:15:48 by mohammoh         ###   ########.fr       */
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
		redirect_fds(data, cmd, i, j);
		if (is_builtin(cmd->cmd_str))
		{
			exec_builtin(cmd, data);
			close_fds(data, i);
			exit(0);
		} 
		else
		{
			
		}
	}
	else
	{
		//global variable status
		waitpid(pid, 0, 0);
		if (!strcmp(cmd->cmd_str, "export"))
			ft_export(cmd->args, data->export_env, data->env);
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
	if (data->cmd_num > 1)
	{
		while (data->cmds[i] != NULL && data->cmds[i]->cmd_str != NULL)
		{
			data->pipe->pid[i] = (data->cmds[i], data, i, j);
			i++;
			j = !j;
		}
	}
	else
		exec_cmd(data->cmds[0], data, 0 , 0);
}