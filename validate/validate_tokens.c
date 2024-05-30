/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:50:58 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/30 20:21:43 by ssibai           ###   ########.fr       */
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
bool	validate_tokens(t_parsing *parse)
{
	int i;

	i = -1;
	while (parse->tokens[++i])
	{
		if (parse->tokens[i]->type == ID)
			return (validate_id(parse, i));
		else if (parse->tokens[i]->type == PIPE)
			return (validate_pipe(parse, i));
		else if (parse->tokens[i]->type == REDIRECT_INPUT
				&& parse->tokens[i]->type == HEREDOC)
			return (validate_input_redirection(parse, i));
		else if (parse->tokens[i]->type == REDIRECT_OUTPUT
				|| parse->tokens[i]->type == REDIRECT_APPEND)
			return (validate_output_redirection(parse, i));
	}
	return (false);
}
