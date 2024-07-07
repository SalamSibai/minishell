

#include "../includes/minishell.h"

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
		data->pipe->pid[0] = exec_cmd(data->cmds[0], data, 0, 0);
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
