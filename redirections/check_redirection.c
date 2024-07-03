/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/03 22:41:00 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_cmd **cmds)
{
	int	i;
	int	redir_value;

	i = -1;
	redir_value = 0;
	while (cmds[++i])
	{
		if (cmds[i]->redirection != NULL)
		{
			redir_value = check_type(cmds[i]);
			if (redir_value < 0)
				return (redir_value);
		}
	}
	return (redir_value);
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
