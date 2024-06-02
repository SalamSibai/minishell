/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:02:50 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/02 21:48:19 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates the ID token
/// @param parse the parse struct
/// @param index the index of the ID we are checking
/// @return true if passed token is valid
bool validate_id(int index, t_data *data)
{
	t_token **tokens;
	
	tokens = data->tokens;
	if (index == 0 || tokens[index - 1]->type == PIPE)
		tokens[index]->type = CMDS;
	else if (tokens[index - 1]->type == REDIRECT_INPUT
			|| tokens[index - 1] ->type == REDIRECT_APPEND
			|| tokens[index - 1]->type == REDIRECT_OUTPUT)
		tokens[index]->type = FILE_NAME;
	else if (tokens[index - 1]->type == HEREDOC)
		tokens[index]->type = LIMITER;
	else if (tokens[index - 1]->type == CMDS)
		tokens[index]->type = EXEC_ID;
	else
	{
		if (is_cmd(tokens[index]->token_string, data))
			tokens[index]->type = CMDS;
		else
			tokens[index]->type = ID;
	}
	return true;
}


