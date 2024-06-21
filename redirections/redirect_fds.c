/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/21 21:57:22 by mohammoh         ###   ########.fr       */
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
			ft_putstr_fd("fd in is a file\n", 1);
			close_fd(data->origin_fds[0]);
			if (!redirect_file_input(cmd))
				return (false);
		}
		else
		{
			cmd->fd_in = dup(STDIN_FILENO);
			if (cmd->fd_in == -1)
			{
				ft_putstr_fd("still -1\n", 1);
				return (false);
			}
			data->origin_fds[0] = dup(STDIN_FILENO);
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			{
				ft_putstr_fd("failed at input\n", 1);
				return (false);
			}
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
	
/* ************************************************************************** */
/*									OUTPUT								  */
/* ************************************************************************** */

	if (i == data->cmd_num - 1)
	{
		//printf("last cmd\n");
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
			cmd->fd_out = dup(STDOUT_FILENO);
			if (cmd->fd_out == -1)
			{
				ft_putstr_fd("still -1\n", 1);
				return (false);
			}
			data->origin_fds[0] = dup(STDOUT_FILENO);
			if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			{
				ft_putstr_fd("failed at input\n", 1);
				return (false);
			}
		}
	}
	else
	{
		if (cmd->fd_out != -1)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
		}
		if (!redirect_pipe_output(data->pipe, j))
		{
			printf("failed at output\n");
			return (false);
		}
	}
	return (true);
}

