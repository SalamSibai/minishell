/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:05:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/02 22:26:21 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates the pipe token syntax
/// @param parse the parse struct
/// @param index the index of the pipe
/// @return true if the sytnax of the pipe is valid
bool	validate_pipe(t_token **tokens, int index)
{
	if (index == 0)
		return (false);
	else
	{
		if (tokens[index + 1] != NULL)
		{
			if ((tokens[index - 1]->type == CMDS
				|| tokens[index - 1]->type == FILE_NAME
				|| tokens[index - 1]->type == LIMITER
				|| tokens[index - 1]->type == REDIRECT_OUTPUT
				|| tokens[index - 1]->type == DQOUTES
				|| tokens[index - 1]->type == SQOUTES
				||(tokens[index - 2]->type == CMDS && tokens[index - 1]->type == ID)
				||(tokens[index - 2]->type == CMDS && tokens[index - 1]->type == FLAG))
				&& ((tokens[index + 1]->type == ID
				|| tokens[index + 1]->type == REDIRECT_INPUT
				|| tokens[index + 1]->type == REDIRECT_OUTPUT
				|| tokens[index + 1]->type == REDIRECT_APPEND
				|| tokens[index + 1]->type == HEREDOC)))
				return (true);
		}
	}
	return (false);
}
