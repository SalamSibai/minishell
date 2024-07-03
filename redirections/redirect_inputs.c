/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:49:48 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/03 20:34:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	redirect_file_input(t_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (false);
	close(cmd->fd_in);
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
	close(pipe->fd[j][0]);
	return (true);
}

bool	redirect_stdin(t_data *data, t_cmd *cmd)
{
	if (dup2(data->origin_fds[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("failed at input!!!!!!\n", 1);
		return (false);
	}
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	return (true);
}
