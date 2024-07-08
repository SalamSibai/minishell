/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 22:00:39 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief executes the command in the child
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @param i command index
 * @param cmd_exist whether the command exists or not
 * @return int the exit code of that execution
 */
int	exec_child(t_cmd *cmd, t_data *data, int i, bool *cmd_exist)
{
	if (join_cmd_and_flag(cmd))
	{
		if (is_directory(cmd->cmd_str))
		{
			if (ft_strncmp(cmd->cmd_str, "./", 2) == 0)
				return (error_handler(DIR_MSG, DIR_EXEC_ER, data, false), 126);
			return (error_handler(DIR_MSG, DIR_EXEC_ER, data, false), 127);
		}
		if (!get_path(data, cmd, cmd_exist))
		{
			if (ft_strncmp(cmd->cmd_str, "./", 2) == 0)
				return (set_env_and_path(data, FREE),
					error_handler(PATH_ER_MSG, PATH_ER, data, true), 127);
		}
		else
			exec_in_v(cmd, data, i, cmd_exist);
	}
	return (0);
}

/**
 * @brief execute the command in the parent
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @param i command index
 * @param j pipe "flip flop"
 * @return int returns the pid of that process
 */
int	exec_parent(t_cmd *cmd, t_data *data, int i, int j)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (cmd->cmd_str != NULL)
	{
		if (is_builtin(cmd->cmd_str) && data->cmd_num == 1)
		{
			if (!redirect_fds(data, cmd, i, j))
			{
				close_origin_fds(data);
				close_all_fds(3);
			}
			data->g_exit_status = exec_builtin(cmd, data);
		}
	}
	if (i > 0)
		close(data->pipe->fd[!j][0]);
	if (i < data->cmd_num - 1)
		close(data->pipe->fd[j][1]);
	dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	close_origin_fds(data);
	return (0);
}

/**
 * @brief 	checks if the command is a builtin, 
 * 			env builtin, or something to be executed
 * 			in execve.
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @param i command index
 */
void	check_cmd(t_cmd *cmd, t_data *data, int i)
{
	bool	cmd_exist;
	int		exit_code;

	exit_code = -1;
	cmd_exist = true;
	if (cmd->cmd_str != NULL)
	{
		exit_code = check_builtin(cmd, data);
		if (exit_code != -1)
		{
			exit (exit_code);
		}
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

/**
 * @brief 	called if multiple commands are entered into the terminal.
 * 			loops through and executes each command entered.
 * @param data data struct reference
 * @param i cmd index
 * @return true if the execution, creation of pipes, and everything passes
 * @return false false if making pipes fails.
 */
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
			{
				error_handler(PIPE_ER_MSG, PIPE_ER, data, false);
				return (false);
			}
		}
		j = !j;
	}
	close_pipe(data->pipe, !j, false);
	return (true);
}
