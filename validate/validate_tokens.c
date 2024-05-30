/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:50:58 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/30 19:10:10 by ssibai           ###   ########.fr       */
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

bool	validate_id(t_parsing *parse, int index)
{
	if (index == 0)
		parse->tokens[index]->type = CMDS;
	else
	{
		if (parse->tokens[index - 1]->type == REDIRECT_INPUT
			|| parse->tokens[index - 1]->type == REDIRECT_APPEND
			|| parse->tokens[index - 1]->type == REDIRECT_OUTPUT)
				parse->tokens[index - 1]->type = CMDS;
		else if (parse->tokens[index - 1]->type == HEREDOC)
			parse->tokens[index - 1]->type = LIMITER;
		else
			parse->tokens[index]->type = CMDS;
	}
	return (true);
}



bool	validate_pipe(t_parsing *parse, int index)
{
	if (index == 0)
		return (false);
	else
	{
		if (parse->tokens[index - 1]->type == CMDS
			&& parse->tokens[index + 1]->type === ID)
			return (true);
	}
	return (false);
}



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
			return (validate_pipe(parse, i))
		else if (parse->tokens[i]->type == REDIRECT_INPUT)
			//validate input redirection
		else if (parse->tokens[i]->type == REDIRECT_OUTPUT
				|| parse->tokens[i]->type == REDIRECT_APPEND)
			//validate output redirection
		else if (parse->tokens[i]->type == HEREDOC)
			//validate heredoc
		else if (parse->tokens[i]->type == DQOUTES)
			//validate dqoutes
		else if (parse->tokens[i]->type == SQOUTES)
			//validate sqoutes
	}
	return (true);
}
