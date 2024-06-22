/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:49:48 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/22 17:54:17 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	redirect_file_input(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (false);
	ft_putstr_fd("successful redirection\n", 1);
	return (true);
}

/// @brief dup2 the input to the correct pipe
/// @param pipe the pipe struct
/// @param j flipflop
/// @return true if passes
bool	redirect_pipe_input(t_pipe *pipe, int j)
{
	ft_putnbr_fd(j, 1);
	ft_putstr_fd("\nREADING FROM PIPE\n", 1);
	if (dup2(pipe->fd[j][0], STDIN_FILENO) == -1)
		return (false);
	return (true);
}

bool	redirect_stdin(t_data *data, t_cmd *cmd)
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
	return (true);
}
