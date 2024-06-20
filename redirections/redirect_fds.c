/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/20 21:03:48 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	// check_redirections(data->cmds);

	/*
	check number of comands
		if 1: execute that comand and print into the redirected fd if available

		if its the last command:
			redirect to whatever the last output redirection is (if available)
			otherwise print on std out
			
		else:
			redirect to the pipe (write end) ONLY IF THERES NO REDIRECTION OUTPUT
		
		when reading:

		if its the first command:
			read from either the file, the heredoc (redir->fd), or stdin (ONLY IF PASSES)
		else
			read from the read end of the previous pipe 
	*/
bool	redirect_fds(t_data *data,t_cmd *cmd, int i, int j)
{
	if (i == 0)
	{
		if (cmd->fd_in != -1)
		{
			close_fd(data->origin_fds[0]);
			if (!redirect_file_input(cmd))
				return (false);
		}
		else
		{
			data->origin_fds[0] = dup(STDIN_FILENO);
			close_fd(STDIN_FILENO);
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				return (false);
			return (true);
		}
	}
	else
	{
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
				return (false);
		}
		else
		{
			if (!redirect_pipe_input(data->pipe, !j))
				return (false);
		}
	}
	
/* ************************************************************************** */
/*									OUTPUT								  */
/* ************************************************************************** */

	if (i == data->cmd_num - 1)
	{
		if (cmd->fd_out != -1)
		{
			if (!redirect_file_output(cmd))
				return (false);
			else
			{
				data->origin_fds[1] = dup(STDOUT_FILENO);
				close_fd(STDOUT_FILENO);
				if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
					return (false);
				return (true);
			}
		}
		else
		{
			if (cmd->fd_out != -1)
			{
				dup2(cmd->fd_out, STDOUT_FILENO);
			}
			if (!redirect_pipe_output(data->pipe, j))
				return (false);
		}
	}
	return (true);
}
