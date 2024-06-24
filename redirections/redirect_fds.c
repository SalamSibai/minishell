/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/24 19:59:44 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	redirect_inputs(t_data *data,t_cmd *cmd, int i, int j)
{
	if (i == 0)
	{
		// data->origin_fds[0] = dup(STDIN_FILENO);
		// data->origin_fds[1] = dup(STDOUT_FILENO);
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
				return (false);
		}
		else if (!redirect_stdin(data, cmd))
			return (false);
	}
	else
	{
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
				return (false);
		}
		else if (!redirect_pipe_input(data->pipe, !j))
			return (false);
	}
	return (true);
}

static bool	redirect_outputs(t_data *data,t_cmd *cmd, int i, int j)
{
	if (i == data->cmd_num - 1)
	{
		if (cmd->fd_out != -1)
		{
			if (!redirect_file_output(cmd))
				return (false);
		}
		else if (!redirect_stdout(data, cmd))
			return (false);
	}
	else
	{
		if (cmd->fd_out != -1)
		{
			if (!redirect_file_output(cmd))
				return (false);
		}
		else if (!redirect_pipe_output(data->pipe, j))
			return (false);
	}
	return (true);
}

bool	redirect_fds(t_data *data,t_cmd *cmd, int i, int j)
{
	if (!redirect_inputs(data, cmd, i, j))
		return (false);
	if (!redirect_outputs(data, cmd, i, j))
		return (false);
	return (true);
}
