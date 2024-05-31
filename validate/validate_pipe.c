/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:05:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/31 21:04:29 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates the pipe token syntax
/// @param parse the parse struct
/// @param index the index of the pipe
/// @return true if the sytnax of the pipe is valid
bool	validate_pipe(t_parsing *parse, int index)
{
	if (index == 0)
		return (false);
	else
	{
		if (parse->tokens[index + 1] != NULL)
		{
			if (index == 1)
			{
				if (parse->tokens[index - 1] )
				
			}
			if (index >= 2)
			{
				if (
					|| parse->tokens[index - 1]->type == FILE_NAME
					|| parse->tokens[index - 1]->type == LIMITER
					|| parse->tokens[index - 1]->type == REDIRECT_OUTPUT
					|| parse->tokens[index - 1]->type == DQOUTES
					|| parse->tokens[index - 1]->type == SQOUTES
					||( parse->tokens[index - 2]->type == CMDS && parse->tokens[index - 1]->type == ID))
					&& parse->tokens[index + 1]->type == ID)
					return (true);
			}
			else
			
	}
	return (false);
}
