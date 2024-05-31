/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:02:50 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/31 20:56:34 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates the ID token
/// @param parse the parse struct
/// @param index the index of the ID we are checking
/// @return true if passed token is valid
bool validate_id(t_parsing *parse, int index, t_data *data)
{
	if (index == 0 || parse->tokens[index - 1]->type == PIPE)
		parse->tokens[index]->type = CMDS;
	else if (parse->tokens[index - 1]->type == REDIRECT_INPUT
			|| parse->tokens[index - 1]->type == REDIRECT_APPEND
			|| parse->tokens[index - 1]->type == REDIRECT_OUTPUT)
		parse->tokens[index]->type = FILE_NAME;
	else if (parse->tokens[index - 1]->type == HEREDOC)
		parse->tokens[index]->type = LIMITER;
	else if (parse->tokens[index - 1]->type == CMDS)
		parse->tokens[index]->type = EXEC_ID;
	else
	{
		if (is_cmd(parse->tokens[index]->token_string, data))
			parse->tokens[index]->type = CMDS;
		else
			parse->tokens[index]->type = ID;
	}
	return true;
}
