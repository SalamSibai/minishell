/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/14 19:47:24 by ssibai           ###   ########.fr       */
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

/// @brief checks the type of the redirection, and calls the
//			corresponding function to store the fd of 
//			that redirection
/// @param redir redirection struct
void	check_type(t_redirection *redir)
{
	t_redirection	*temp;

	temp = redir;
	while (temp)
	{
		if (temp->type == REDIRECT_INPUT)
		{
			if (!get_input(redir, false))
				temp->type = REDIR_INPUT_FAILED;
		}
		else if (temp->type == HEREDOC)
		{
			if (!get_input(redir, true))
				temp->type = REDIR_INPUT_FAILED;
		}
		temp ++;
		// else if (temp->type == REDIRECT_OUTPUT)
		// {
			
		// }
	}
}