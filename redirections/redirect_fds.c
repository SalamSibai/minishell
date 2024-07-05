/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/03 22:41:22 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	redirect_inputs(t_data *data,t_cmd *cmd, int i, int j)
{
	if (i == 0)
	{
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
			{
				return (false);
			}
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
	bool	input_redir;
	bool	output_redir;

	input_redir = redirect_inputs(data, cmd, i, j);
	output_redir = redirect_outputs(data, cmd, i, j);
	if (!input_redir)
	{
		return (error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, data, false), false);
	}
	if (!output_redir)
	{
		ft_putstr_fd("FAILED OUT\n", 2);
		return (error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, data, false), false);
	}
	return (true);
}
