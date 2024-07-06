/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:50:58 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/06 16:07:26 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static bool	validate_tokens_helper()
// {
// }

/// @brief validates whether the tokens provided are syntactically correct
/// @param parse the parse struct
/// @return true if all passed tokens are valid
bool	validate_tokens(t_data *data)
{
	t_token	**tokens;
	int		i;

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
