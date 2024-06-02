/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:23:56 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/02 21:36:11 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	init_redirections(t_redirection *redir)
{
	redir->fd = -1;
	redir->type = NONE;
	redir->file_name = '\0';
	redir->limiter = '\0';
}

bool	init_cmd(t_cmd *cmd)
{
	cmd->cmd_str = '\0';
	cmd->args_str = NULL;
	cmd->redirection = NULL;
}
