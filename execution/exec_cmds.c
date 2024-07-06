/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/05 05:44:37 by mohammoh         ###   ########.fr       */
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
	int		pid;
	int		redir_return;
	bool	cmd_exist;

	cmd_exist = true;
	redir_return = 0;
    data->origin_fds[0] = dup(STDIN_FILENO);
    data->origin_fds[1] = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		return (error_handler(FORK_ER_MSG, FORK_ER, data, false), pid);
	if (pid == 0)
	{
		redir_return = check_redirections(cmd, data->env);
		if (redir_return < 0)
		{
			if (redir_return == -1)
				error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, data, true);
			else
				error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, data, true);
		}
		if (!redirect_fds(data, cmd, i, j))
		{
			close_everything();
			close_origin_fds(data);
			free_cmd(data);
			set_env_and_path(data, FREE);
			cleanup(data);
			exit(1);
		}
		close_origin_fds(data);
		if (cmd->cmd_str != NULL)
		{
			if (is_builtin(cmd->cmd_str) && (data->cmd_num > 1))
			{
				exec_builtin(cmd, data);
				for (int fd=0; fd<64; fd++) (void) close(fd);
				free_cmd(data);
				set_env_and_path(data, FREE);
				cleanup(data);
				exit(0);
			}
			if (is_env_builtin(cmd->cmd_str) || (is_builtin(cmd->cmd_str) && (data->cmd_num == 1)) )
			{
				for (int fd=0; fd<64; fd++) (void) close(fd);
				set_env_and_path(data, FREE);
				free_cmd(data);
				cleanup(data);
				exit (0);
			}
			else
			{
				if (join_cmd_and_flag(cmd))
				{
					if (!get_path(data, cmd, &cmd_exist))
					{
						free_cmd(data);
						set_env_and_path(data, FREE);
						error_handler(PATH_ER_MSG, PATH_ER, data, true);
					}
					else
					{
						if (cmd_exist)
						{
							close_everything();
							execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
						}
						else
						{
							close_fds(data, i, true);
							set_env_and_path(data, FREE);
							//free_cmd(data);
							error_handler(CMD_ER_MSG, CMD_ER, data, true);
						}
					}
				}
			}
		}
	}
	else
	{
		if (cmd->cmd_str != NULL)
		{
			if (redir_return < 0)
			{
				if (redir_return == -1)
					error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, data, true);
				else
					error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, data, true);
			}
			if (is_builtin(cmd->cmd_str) && data->cmd_num == 1)
			{
				pid = getpid();
				redir_return = check_redirections(cmd, data->env);
				if (!redirect_fds(data, cmd, i, j))
				{
					close_origin_fds(data);
					for (int fd=3; fd<64; fd++) (void) close(fd);
					return (pid);
				}
				exec_builtin(cmd, data);
				dup2(data->origin_fds[0], STDIN_FILENO);
				dup2(data->origin_fds[1], STDOUT_FILENO);
				close_origin_fds(data);
				for (int fd=3; fd<64; fd++) (void) close(fd);
				return (pid);
			}
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
	int status;
	
	status = 0;
	//signal(SIGPIPE, SIG_IGN);
	i = 0;
	j = 0;
//	if (data->cmds[0]->cmd_str == NULL)
//		return (true);
	alloc_pids(data);
	if (data->cmd_num > 1)
	{
		if (!make_pipes(data->pipe))
			return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
		while (data->cmds[i] != NULL)
		{
			data->pipe->pid[i] = exec_cmd(data->cmds[i], data, i, j);
			if (i >= 1 && i < data->cmd_num - 1)
			{
				close_pipe(data->pipe, !j, false);
				if (pipe(data->pipe->fd[!j]) == -1)
					return (error_handler(PIPE_ER_MSG, PIPE_ER, data, false), false);
			}
			i++;
			j = !j;
		}
		close_pipe(data->pipe, !j, false);
	}
	else
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
	i = -1;
	while (++i < data->cmd_num)
		close_fds(data, i, false);
	i = -1;

    while (++i < data->cmd_num)
    {
        waitpid(data->pipe->pid[i], &status, 0);
        if (i == data->cmd_num - 1)  // Only update g_exit_status for the last command
        {
            if (WIFEXITED(status))
                g_exit_status = WEXITSTATUS(status);
        }
    }
	dup2(STDIN_FILENO, data->origin_fds[0]);
	dup2(STDOUT_FILENO, data->origin_fds[1]);
	close_origin_fds(data);
	close_everything();
	return (true);
}
