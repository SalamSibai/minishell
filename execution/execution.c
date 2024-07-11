/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:06:31 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 21:07:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	single_cmd_builtin_redi(t_data *data, bool *duped_in, bool *duped_out)
{
	if (!set_redir(data->cmds[0], data))
        return (false);
    if (data->cmds[0]->fd_in != -1)
	{
		dup2(data->cmds[0]->fd_in, STDIN_FILENO);
		close(data->cmds[0]->fd_in);  // Close the fd_in after duplication
		*duped_in = true;
	}
	if (data->cmds[0]->fd_out != -1)
	{
		dup2(data->cmds[0]->fd_out, STDOUT_FILENO);
		close(data->cmds[0]->fd_out);  // Close the fd_out after duplication
		*duped_out = true;
	}
	return (true);
}

/**
 * @brief this function will execute the commands based on the type of command
 * either its a builtin or a command to be executed in the parent or the child
 * @param data 
 */
bool	execute_single_cmd(t_data *data)
{
	bool	duped_in;
	bool	duped_out;
	int		out;
	int		in;  // Added this line to store the original stdin

	duped_in = false;
	duped_out = false;
	if (is_builtin(data->cmds[0]->cmd_str))
	{
		out = dup(STDOUT_FILENO);
		in = dup(STDIN_FILENO);  // Duplicate the original stdin
		if (!single_cmd_builtin_redi(data, &duped_in, &duped_out))
			return (false);
		data->g_exit_status = exec_builtin(data->cmds[0], data);
		if (duped_in)
		{
			dup2(in, STDIN_FILENO);  // Restore the original stdin
			close(in);  // Close the duplicated stdin
		}
		if (duped_out)
		{
			dup2(out, STDOUT_FILENO);  // Restore the original stdout
			close(out);  // Close the duplicated stdout
		}
	}
	else
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
	return (true);
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
	{

		if (!execute_single_cmd(data))
			return (false);
	}
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
