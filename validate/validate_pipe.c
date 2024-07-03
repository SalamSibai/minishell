/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:05:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/02 20:08:57 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	valid_before_pipe(t_token **tokens, int index)
{
	int i = index - 1;
	while (i >= 0) 
	{
		if (tokens[i]->type == CMDS || tokens[i]->type == FILE_NAME ||
			tokens[i]->type == LIMITER || tokens[i]->type == REDIRECT_OUTPUT ||
			tokens[i]->type == DQOUTES || tokens[i]->type == SQOUTES ||
			tokens[i]->type == ID || tokens[i]->type == FLAG) 
		{
			return (true);
		}
		i--;
	}
	return (false);
}
static bool	valid_after_pipe(t_token **tokens, int index)
{
	t_token_type	next_type;
	bool			after_pipe;
	
	if (tokens[index + 1] != NULL) 
	{
		next_type = tokens[index + 1]->type;
		after_pipe = (next_type == CMDS ||
						next_type == ID ||
						next_type == REDIRECT_INPUT ||
						next_type == REDIRECT_OUTPUT ||
						next_type == REDIRECT_APPEND ||
						next_type == HEREDOC);
		return (after_pipe);
	}
	return (false);  // Pipe cannot be at the end
}
/// @brief validates the pipe token syntax
/// @param parse the parse struct
/// @param index the index of the pipe
/// @return true if the sytnax of the pipe is valid
bool validate_pipe(t_token **tokens, int index)
{
	bool	before_pipe;
	bool	after_pipe;
	
	if (index == 0)
		return false;
	before_pipe = valid_before_pipe(tokens, index);
	after_pipe = valid_after_pipe(tokens, index);
	return (before_pipe && after_pipe); 
}
