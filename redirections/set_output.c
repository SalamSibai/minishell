/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:41:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/18 21:26:21 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	set_output(t_cmd *cmd, bool append, t_redirection *redir)
{
	if (!append)
	{
		cmd->fd_out = open(redir->file_name,
				O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (!cmd->fd_out)
			return (false);
	}
	else
	{
		cmd->fd_out =  open(redir->file_name,
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (!cmd->fd_out)
			return (false);
	}
	return (true);
}
