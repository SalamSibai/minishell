/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:50:58 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/02 20:06:53 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	to validate the entire input:
		1) if only 1 id, must be an executable that works
		2) if heredoc, next token must be an ID
		3) if redirection into a file (>), its fine.
		4) if appending into a file, its fine
		
		 we must have an ID that is not an executable
		5) if redirection from a file, the file we are redirecting from must exist in the directory provided
		6) NO DOUBLE REDIRECTIONS AFTER ONE ANOTHER (except heredoc)
		7) a pipe must have an input its reading from, and an output its reading to
*/




/// @brief validates whether the tokens provided are syntactically correct
/// @param parse the parse struct
/// @return true if all passed tokens are valid
bool	validate_tokens(t_data *data) //NOTE: add t_data *data to check to send the id to validate id to check if its executable or not 
{
	int i;
	t_token **tokens;

	tokens = data->tokens;
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == ID)
		{
			if (!validate_id(i, data))
				return (false);
		}
		else if (tokens[i]->type == PIPE)
		{
			if (!validate_pipe(tokens, i))
				return (false);
			data->cmd_num++;
			data->cmd_ctr = 0;
		}
		else if (tokens[i]->type == REDIRECT_INPUT
				|| tokens[i]->type == HEREDOC)
		{
			if (!validate_input_redirection(tokens, i))
				return (false);
		}
		else if (tokens[i]->type == REDIRECT_OUTPUT
				|| tokens[i]->type == REDIRECT_APPEND)
		{
			if (!validate_output_redirection(tokens, i))
				return (false);
		}
		else if (tokens[i]->type == DQOUTES || tokens[i]->type == SQOUTES)
		{
			validate_qoutes(i, data);
			if (tokens[i]->type == PIPE)
			{
				data->cmd_num++;
				data->cmd_ctr = 0;
			}
		}
	}
	return (true);
}
