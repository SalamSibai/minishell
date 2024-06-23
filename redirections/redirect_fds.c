/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/23 17:13:03 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	redirect_fds(t_data *data,t_cmd *cmd, int i, int j)
{
	if (i == 0)
	{
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
				return (false);
		}
		else
		{
			if (!redirect_stdin(data, cmd))
				return (false);
		}
	}
	else
	{
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
			{
				printf("failed at input\n");
				return (false);
			}
		}
		else
		{
			if (!redirect_pipe_input(data->pipe, !j))
			{
				printf("failed at input\n");
				return (false);
			}
		}
	}
	if (i == data->cmd_num - 1)
	{
		if (cmd->fd_out != -1)
		{
			if (!redirect_file_output(cmd))
			{
				printf("failed at output\n");
				return (false);
			}
		}
		else
		{
			if (!redirect_stdout(data, cmd))
				return (false);
		}
	}
	else
	{
		if (cmd->fd_out != -1)
		{
			if (!redirect_file_output(cmd))
			{
				printf("failed at output\n");
				return (false);
			}
		}
		else if (!redirect_pipe_output(data->pipe, j))
		{
			printf("failed at output\n");
			return (false);
		}
	}
	return (true);
}

