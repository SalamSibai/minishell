/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/19 21:09:50 by mohammoh         ###   ########.fr       */
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
			check_type(cmds[i]);
		}
	}
}

/// @brief checks the type of the redirection, and calls the
//			corresponding function to store the fd of 
//			that redirection
/// @param redir redirection struct
int	check_type(t_cmd *cmd)
{
	t_redirection	*temp;
	int				ret_value;

	ret_value = 0;
	temp = cmd->redirection;
	while (temp)
	{
		if (temp->type == REDIRECT_INPUT)
		{
			if (!get_input(cmd, false, temp))
			{
				temp->type = REDIR_INPUT_FAILED;
				ret_value = -1;
			}
		}
		else if (temp->type == HEREDOC)
		{
			if (!get_input(cmd, true, temp))
			{
				temp->type = REDIR_INPUT_FAILED;
				ret_value = -1;
			}
		}
		else if (temp->type == REDIRECT_OUTPUT)
		{
			if (!set_output(cmd, false, temp))
			{
				temp->type = REDIR_OUTPUT_FAILDED;
				ret_value = -2;
			}
		}
		else if (temp->type == REDIRECT_APPEND)
		{
			if (!set_output(cmd, true, temp))
			{
				temp->type = REDIR_OUTPUT_FAILDED;
				ret_value = -2;
			}
		}
		temp = temp->next;
	}
	return (ret_value);
}