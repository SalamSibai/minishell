/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:23:56 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/03 16:56:03 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void	init_redirections(t_redirection *redir)
{
	redir->fd = -1;
	redir->type = NONE;
	redir->file_name = NULL;
	redir->limiter = NULL;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd_str = NULL;
	cmd->args_str = NULL;
	cmd->redirection = NULL;
}
