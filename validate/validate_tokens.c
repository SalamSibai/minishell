/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:50:58 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/08 22:31:29 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokens_itir(t_data *data, int i, t_token **tokens)
{
	while (tokens[++i])
	{
		if (if_id(data, i, tokens) == -1)
			return ;
		else if (if_id(data, i, tokens) == 1)
			continue ;
		if (if_pipe(data, i, tokens) == -1)
			return ;
		else if (if_pipe(data, i, tokens) == 1)
			continue ;
		if (if_input(i, tokens) == -1)
			return ;
		else if (if_input(i, tokens) == 1)
			continue ;
		if (if_output(i, tokens) == -1)
			return ;
		else if (if_output(i, tokens) == 1)
			continue ;
		if (if_quote_or_dquote(i, tokens, data) == -1)
			return ;
		else if (if_quote_or_dquote(i, tokens, data) == 1)
			continue ;
	}
}

/// @brief validates whether the tokens provided are syntactically correct
/// @param parse the parse struct
/// @return true if all passed tokens are valid
bool	validate_tokens(t_data *data)
{
	t_token	**tokens;
	int		i;

	tokens = data->tokens;
	i = -1;
	tokens_itir(data, i, tokens);
	return (true);
}
