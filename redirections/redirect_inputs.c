/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:49:48 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/20 21:02:10 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// bool	redirect_input(t_cmd *cmd, t_data *data, int i, int j)
// {
// 	if (i == 0)
// 	{
// 		if (cmd->fd_in != -1)
// 		{
// 			close_fd(data->origin_fds[0]);
// 			if (!redirect_file_input(cmd))
// 				return (false);
// 		}
// 		else
// 		{
// 			data->origin_fds[0] = dup(STDIN_FILENO);
// 			close_fd(STDIN_FILENO);
// 			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
// 				return (false);
// 			return (true);
// 		}
// 	}
// 	else
// 	{
// 		if (cmd->fd_in != -1)
// 		{
// 			if (!redirect_file_input(cmd))
// 				return (false);
// 		}
// 		else
// 		{
// 			if (!redirect_pipe_input(data->pipe, !j))
// 				return (false);
// 		}
// 	}
// }