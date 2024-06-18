/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/18 21:27:10 by ssibai           ###   ########.fr       */
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
			check_type(cmds[i]);
		}
	}
}

/// @brief checks the type of the redirection, and calls the
//			corresponding function to store the fd of 
//			that redirection
/// @param redir redirection struct
void	check_type(t_cmd *cmd)
{
	t_redirection	*temp;

	temp = cmd->redirection;
	while (temp)
	{
		if (temp->type == REDIRECT_INPUT)
		{
			if (!get_input(cmd, false, temp))
				temp->type = REDIR_INPUT_FAILED;
		}
		else if (temp->type == HEREDOC)
		{
			if (!get_input(cmd, true, temp))
				temp->type = REDIR_INPUT_FAILED;
		}
		else if (temp->type == REDIRECT_OUTPUT)
		{
			if (!set_output(cmd, false, temp))
				temp->type = REDIR_OUTPUT_FAILDED;
		}
		else if (temp->type == REDIRECT_APPEND)
		{
			if (!set_output(cmd, true, temp))
				temp->type = REDIR_OUTPUT_FAILDED;
		}
		temp = temp->next;
	}
}