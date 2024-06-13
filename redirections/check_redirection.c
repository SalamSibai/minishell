/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/13 19:36:15 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redirections(t_cmd **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]->redirection != NULL)
		{
			check_type(cmds[i]->redirection);
		}
	}
}

void	check_type(t_redirection *redir)
{
	t_redirection	*temp;

	temp = redir;
	while (temp)
	{
		// if (temp->type == HEREDOC)
		// {
			
		// }
		if (temp->type == REDIRECT_INPUT)

	}
}