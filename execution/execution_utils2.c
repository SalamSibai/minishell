

#include "../includes/minishell.h"

bool	set_redir(t_cmd *cmd, t_data *data)
{
	int		redir_return;

	redir_return = 0;
	redir_return = check_redirections(cmd, data->env);
	if (redir_return < 0)
	{
		if (redir_return == -1)
			error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, data, false);
		else
			error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, data, false);
		return (false);
	}
	return (true);
}

void	dup_origin(t_data *data)
{
	data->origin_fds[0] = dup(STDIN_FILENO);
	data->origin_fds[1] = dup(STDOUT_FILENO);
	data->duped = true;
}

bool	exec_redir(t_data *data, t_cmd *cmd, int i, int j)
{
	if (!redirect_fds(data, cmd, i, j))
	{
		close_all_fds(3);
		close_origin_fds(data);
		free_cmd(data);
		set_env_and_path(data, FREE);
		cleanup(data);
		return (false);
	}
	return (true);
}

bool	check_builtin(t_cmd *cmd, t_data *data)
{
	if (is_builtin(cmd->cmd_str) && (data->cmd_num > 1))
	{
		g_exit_status = exec_builtin(cmd, data);
		close_all_fds(0);
		free_cmd(data);
		set_env_and_path(data, FREE);
		cleanup(data);
		return (true);
	}
	return (false);
}

bool	check_env_builtin(t_cmd *cmd, t_data *data)
{
	if (is_env_builtin(cmd->cmd_str) || (is_builtin(cmd->cmd_str)
			&& (data->cmd_num == 1)) )
	{
		for (int fd=0; fd<64; fd++) (void) close(fd);
		set_env_and_path(data, FREE);
		free_cmd(data);
		cleanup(data);
		return (true);
	}
	return (false);
}
