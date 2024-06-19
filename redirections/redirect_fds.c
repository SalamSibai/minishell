/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/19 21:00:52 by ssibai           ###   ########.fr       */
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

bool	redirect_file_input(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (false);
	return (true);
}

/// @brief dup2 the input to the correct pipe
/// @param pipe the pipe struct
/// @param j flipflop
/// @return true if passes
bool	redirect_pipe_input(t_pipe *pipe, int j)
{
	if (dup2(pipe->fd[j][0], STDIN_FILENO) == -1)
		return (false);
	return (true);
}

bool	redirect_file_output(t_cmd *cmd)
{
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (false);
	return (true);
}

bool	redirect_pipe_output(t_pipe *pipe, int j)
{
	if (dup2(pipe->fd[j][0], STDOUT_FILENO) == -1)
		return (false);
	return (true);
}

bool	redirect_fds(t_data *data,t_cmd *cmd, int i, int j)
{
	if (i == 0)
	{
		if (cmd->fd_in != -1)
		{
			if (!redirect_file_input(cmd))
				return (false);
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



	if (i == data->cmd_num - 1)
	{
		if (cmd->fd_out != -1)
		{
			if (!redirect_file_output(cmd))
				return (false);
			else
				dup2(data->origin_fds[1], STDOUT_FILENO);
		}
		else
		{
			if (cmd->fd_out != -1)
			
			if (!redirect_pipe_output(data->pipe, j))
				return (false);
		}
	}
	return (true);
}
