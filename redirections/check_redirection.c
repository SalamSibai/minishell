/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/13 21:34:59 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redirections(t_cmd **cmds)
{
	int	i;
	t_redirection	*tmp;

	i = -1;
	tmp = NULL;
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
		{
			redirect_input(temp);
		}
		else if (temp->type == REDIRECT_OUTPUT)
		{
			redirect_output(temp);
		}
		else if (temp->type == REDIRECT_APPEND)
		{
			redirect_append(temp);
		}

	}
}