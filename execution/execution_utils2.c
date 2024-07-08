/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 20:25:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Set the fd->in and fd->out for each command.
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @return true if setting all passes
 * @return false if setting any (input or output) fails
 */
bool	set_redir(t_cmd *cmd, t_data *data)
{
	int		in_redir_return;
	int		out_redir_return;

	in_redir_return = 0;
	out_redir_return = 0;
	check_redirections(cmd, data, &in_redir_return, &out_redir_return);
	if (in_redir_return == -1)
	{
		error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, data, false);
		return (false);
	}
	if (out_redir_return == -1)
	{
		error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, data, false);
		return (false);
	}
	return (true);
}

/**
 * @brief 	dups the stdin and out into data->origin_fds array
 * 			to maintain a copy of them.
 * @param data data struct reference
 */
void	dup_origin(t_data *data)
{
	data->origin_fds[0] = dup(STDIN_FILENO);
	data->origin_fds[1] = dup(STDOUT_FILENO);
	data->duped = true;
}

/**
 * @brief 	preforms dup2 of set fd->in and fd->out of each cmd
 * @param data data struct reference
 * @param cmd cmd struct reference
 * @param i cmd index
 * @param j pipe "flip flop"
 * @return true if dup passes for all redirection fds
 * @return false if dup fails for any redirection fd
 */
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
 
/**
 * @brief 	checks whether the command is a builtin or not,
 * 			and if there are multiple commands.
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @return true if it is a builtin and there are more than 1 cmds
 * @return false if it is not a builtin OR if it is the only command
 */
int	check_builtin(t_cmd *cmd, t_data *data)
{
	int ret;

	ret = -1;
	if (is_builtin(cmd->cmd_str) && (data->cmd_num > 1))
	{
		data->g_exit_status = exec_builtin(cmd, data);
		ret = data->g_exit_status;
		close_all_fds(0);
		free_cmd(data);
		set_env_and_path(data, FREE);
		cleanup(data);
		return (ret);
	}
	return (ret);
}

/**
 * @brief 	Checks if the command is an env builtin OR if its
 * 			a bultin AND its the only command to be executed in the parent
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @return true if it is an env builtin OR its a builtin and its the only command
 * @return false if its not either of whats above.
 */
bool	check_env_builtin(t_cmd *cmd, t_data *data)
{
	if (is_env_builtin(cmd->cmd_str) || (is_builtin(cmd->cmd_str)
			&& (data->cmd_num == 1)))
	{
		close_all_fds(0);
		set_env_and_path(data, FREE);
		free_cmd(data);
		cleanup(data);
		return (true);
	}
	return (false);
}
