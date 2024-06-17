/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/18 00:27:48 by mohammoh         ###   ########.fr       */
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
			if (!get_input(temp, false))
				temp->type = REDIR_INPUT_FAILED;
		}
		else if (temp->type == HEREDOC)
		{
			if (!get_input(temp, true))
				temp->type = REDIR_INPUT_FAILED;
		}
		else if (temp->type == REDIRECT_OUTPUT)
		{
			if (!set_output(temp, false))
				temp->type = REDIR_OUTPUT_FAILDED;
		}
		else if (temp->type == REDIRECT_APPEND)
		{
			if (!set_output(temp, true))
				temp->type = REDIR_OUTPUT_FAILDED;
		}
		temp = temp->next;
	}
}