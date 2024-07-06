/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/05 07:31:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_cmd *cmd, t_list *env)
{
	int	redir_value;

	redir_value = 0;
	if (cmd->redirection != NULL)
	{
		redir_value = check_type(cmd, env);
		if (redir_value < 0)
			return (redir_value);
	}
	return (redir_value);
}


int	inputs(t_cmd *cmd, t_redirection *redir, bool heredoc, t_list *env)
{
	int	ret_value;

	ret_value = 0;
	if (!get_input(cmd, heredoc, redir, env))
	{
		redir->type = REDIR_INPUT_FAILED;
		ret_value = -1;
	}
	return (ret_value);
}

int outputs(t_cmd *cmd, t_redirection *redir, bool append)
{
	int	ret_value;

	ret_value = 0;
	if (!set_output(cmd, append, redir))
	{
		redir->type = REDIR_OUTPUT_FAILDED;
		ret_value = -2;
	}
	return (ret_value);
}


/// @brief checks the type of the redirection, and calls the
//			corresponding function to store the fd of 
//			that redirection
/// @param redir redirection struct
int	check_type(t_cmd *cmd, t_list *env)
{
	t_redirection	*temp;
	int				ret_value;

	ret_value = 0;
	temp = cmd->redirection;
	while (temp)
	{
		if ((temp->type == REDIRECT_INPUT) || (temp->type == HEREDOC))
		{
			if (temp->type == HEREDOC)
				ret_value = inputs(cmd, temp, true, env);
			else
				ret_value = inputs(cmd, temp, true, env);
		}
		else if ((temp->type == REDIRECT_OUTPUT) || (temp->type == REDIRECT_APPEND))
		{
			if (temp->type == REDIRECT_APPEND)
				ret_value = outputs(cmd, temp, true);
			else
				ret_value = outputs(cmd, temp, false);
		}
		temp = temp->next;
	}
	return (ret_value);
}
