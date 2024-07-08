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

/**
 * @brief calls "set output" to check whether output redir passed or failed
 * @param cmd cmd struct reference
 * @param redir redirection pointer
 * @param append append boolean (true if redir type is append)
 * @return int 0 if redirection passed, negative if it failed
 */
int	outputs(t_cmd *cmd, t_redirection *redir, bool append)
{
	int	ret_value;

	ret_value = 0;
	if (!set_output(cmd, append, redir))
	{
		redir->type = REDIR_OUTPUT_FAILDED;
		ret_value = -1;
	}
	return (ret_value);
}

/**
 * @brief checks the output type whether it is append or overwrite or stdout
 * @param temp the redirection pointer
 * @param cmd cmd struct reference
 * @return true if the redirection was successful
 * @return false if the redirection failed
 */
bool	check_output_type(t_redirection *temp, t_cmd *cmd)
{
	int	redir_value;

	redir_value = 0;
	if ((temp->type == REDIRECT_OUTPUT) || (temp->type == REDIRECT_APPEND))
	{
		if (temp->type == REDIRECT_APPEND)
			redir_value = outputs(cmd, temp, true);
		else
			redir_value = outputs(cmd, temp, false);
		if (redir_value < 0)
			return (false);
	}
	return (true);
}

/**
 * @brief calls "get input" to check whether input redir passed or failed
 * @param cmd cmd struct reference
 * @param redir redirection pointer
 * @param heredoc heredoc boolean (true if redir type is heredoc)
 * @param data data struct reference
 * @return int 0 if redirection passed, negative if it failed
 */
int	inputs(t_cmd *cmd, t_redirection *redir, bool heredoc, t_data *data)
{
	int	ret_value;

	ret_value = 0;
	if (!get_input(cmd, heredoc, redir, data))
	{
		redir->type = REDIR_INPUT_FAILED;
		ret_value = -1;
	}
	return (ret_value);
}

/**
 * @brief checks the input type whether it is heredoc or file or stdin
 * @param temp the redirection pointer
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @return true if the redirection was successful
 * @return false if the redirection failed
 */
bool	check_input_type(t_redirection *temp, t_cmd *cmd, t_data *data)
{
	int	redir_value;

	redir_value = 0;
	if ((temp->type == REDIRECT_INPUT) || (temp->type == HEREDOC))
	{
		if (temp->type == HEREDOC)
			redir_value = inputs(cmd, temp, true, data);
		else
			redir_value = inputs(cmd, temp, false, data);
		if (redir_value < 0)
			return (false);
	}
	return (true);
}

/**
 * @brief	checks each redirection based on its type, and sets
 * 			it to the correct fd as long as it passes
 * @param cmd cmd struct reference
 * @param data data struct reference
 * @param in_val reference to "in_redir_return" from "set_redir" function
 * @param out_val reference to "out_redir_return" from "set_redir" function
 */
void	check_redirections(t_cmd *cmd, t_data *data, int *in_val, int *out_val)
{
	t_redirection	*temp;

	temp = cmd->redirection;
	if (cmd->redirection != NULL)
	{
		while (temp)
		{
			if (!check_input_type(temp, cmd, data))
				*in_val = -1;
			if (!check_output_type(temp, cmd))
				*out_val = -1;
			temp = temp->next;
		}
	}
}
