/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:49:57 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/20 20:50:43 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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