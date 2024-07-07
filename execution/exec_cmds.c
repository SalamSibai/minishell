/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/07 07:27:47 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_child(t_cmd *cmd, t_data *data, int i, bool *cmd_exist)
{
	if (join_cmd_and_flag(cmd))
	{
		if (is_directory(cmd->cmd_str))
			return (error_handler(DIR_EXEC_MSG, DIR_EXEC_ER, data, false), 126);
		if (!get_path(data, cmd, cmd_exist))
			return (set_env_and_path(data, FREE),
				error_handler(PATH_ER_MSG, PATH_ER, data, true), 127);
		else
		{
			if (*cmd_exist)
			{
				close_all_fds(3);
				execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
			}
			else
			{
				close_fds(data, i, true);
				free_cmd(data);
				set_env_and_path(data, FREE);
				error_handler(CMD_ER_MSG, CMD_ER, data, true);
			}
		}
	}
	return (0);
}

int	exec_parent(t_cmd *cmd, t_data *data, int i, int j)
{
	int	pid;

	pid = 0;
	if (cmd->cmd_str != NULL)
	{
		if (is_builtin(cmd->cmd_str) && data->cmd_num == 1)
		{
			pid = getpid();
			if (!redirect_fds(data, cmd, i, j))
			{
				close_origin_fds(data);
				for (int fd=3; fd<64; fd++) (void) close(fd);
			}
			g_exit_status = exec_builtin(cmd, data);
		}
	}
	if (i > 0)
		close(data->pipe->fd[!j][0]);
	if (i < data->cmd_num - 1)
		close(data->pipe->fd[j][1]);
	dup2(data->origin_fds[0], STDIN_FILENO);
	dup2(data->origin_fds[1], STDOUT_FILENO);
	close_origin_fds(data);
	return (pid);
}

void	check_cmd(t_cmd *cmd, t_data *data, int i)
{
	bool	cmd_exist;

	cmd_exist = true;
	if (cmd->cmd_str != NULL)
	{
		if (check_builtin(cmd, data))
			exit (0);
		if (check_env_builtin(cmd, data))
			exit (0);
		exit (exec_child(cmd, data, i, &cmd_exist));
	}
}

/// @brief executes the commands
/// @param cmd pntr to cmd struct
/// @param data pntr to data struct
/// @param i cmd index
/// @param j "flip flop" for pipes
/// @return pid
int	exec_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
	int	pid;

	if (!set_redir(cmd, data))
		return (-1);
	else
	{
		dup_origin(data);
		pid = fork();
		if (pid == -1)
			return (error_handler(FORK_ER_MSG, FORK_ER, data, false), pid);
		if (pid == 0)
		{
			if (!exec_redir(data, cmd, i, j))
				exit(24);
			close_origin_fds(data);
			check_cmd(cmd, data, i);
			exit (0);
		}
		else
			pid = exec_parent(cmd, data, i, j);
	}
	return (pid);
}

bool	exec_multiple(t_data *data, int i)
{
	int	j;

	j = 0;
	if (!make_pipes(data->pipe))
		return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
	while (data->cmds[++i] != NULL)
	{
		data->pipe->pid[i] = exec_cmd(data->cmds[i], data, i, j);
		if (i >= 1 && i < data->cmd_num - 1)
		{
			close_pipe(data->pipe, !j, false);
			if (pipe(data->pipe->fd[!j]) == -1)
				return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
		}
		j = !j;
	}
	close_pipe(data->pipe, !j, false);
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
	int status;
	
	status = 0;
	i = -1;
	alloc_pids(data);
	if (data->cmd_num > 1)
	{
		if (!exec_multiple(data, i))
			return (false);
	}
	else
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
//	close_all_fds(3);
	i = -1;
	if (data->duped)
		reset_fds(data);
	if (data->cmd_num > 1)
	{
		//processes_queue(data, &status);
		i = -1;
		while (++i < data->cmd_num)
		{
			waitpid(data->pipe->pid[i], &status, 0);
			if (i == data->cmd_num - 1 && !is_builtin(data->cmds[i]->cmd_str))
			{
				if (WIFEXITED(status) && (!is_builtin(data->cmds[i]->cmd_str)))
					data->g_exit_status = WEXITSTATUS(status);
			}
		}
	}
	else if (data->cmds[0]->cmd_str && !is_builtin(data->cmds[0]->cmd_str) && data->pipe->pid[0] != -1)
	{
		waitpid(data->pipe->pid[0], &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	return (true);
}
