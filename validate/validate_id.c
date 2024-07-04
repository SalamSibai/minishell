/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:02:50 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/04 06:01:57 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates the ID token
/// @param parse the parse struct
/// @param index the index of the ID we are checking
/// @return true if passed token is valid
bool	validate_id(int i, t_data *data)
{
	t_token	**tokens;

	tokens = data->tokens;
	if (i == 0 || tokens[i - 1]->type == PIPE || tokens[i - 1]->type == LIMITER
		|| tokens[i - 1]->type == FILE_NAME)
	{
		if (data->cmd_ctr == 0)
		{
			data->cmd_ctr++;
			tokens[i]->type = CMDS;
		}
		else
			tokens[i]->type = ID;
	}
	else if (tokens[i - 1]->type == REDIRECT_INPUT
		|| tokens[i - 1]->type == REDIRECT_APPEND
		|| tokens[i - 1]->type == REDIRECT_OUTPUT)
		tokens[i]->type = FILE_NAME;
	else if (tokens[i - 1]->type == HEREDOC)
		tokens[i]->type = LIMITER;
	else if (tokens[i - 1]->type == CMDS)
		tokens[i]->type = ID;
	else
		tokens[i]->type = ID;
	return (true);
}
