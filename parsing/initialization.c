/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:23:56 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/04 21:37:02 by mohammoh         ###   ########.fr       */
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

void	init_cmds(t_cmd **cmds, int cmd_num)
{
	int i;

	i = 0;
	while (i < cmd_num)
	{
		cmds[i] = ft_safe_malloc(sizeof(t_cmd), "CMD");
		cmds[i]->cmd_str = NULL;
		cmds[i]->args_str = NULL;
		cmds[i]->redirection = ft_safe_malloc(sizeof(t_redirection *), "REDIRECTION");
		init_redirections(cmds[i]->redirection);
		i++;
	}
}
