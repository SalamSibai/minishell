/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_output_redirection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:30:29 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/03 13:38:55 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates output redirection
/// @param parse the parsing struct
/// @param index index of token
/// @return true if the token is valid
bool	validate_output_redirection(t_token **tokens, int index)
{
	if (tokens[index + 1] != NULL)
	{
		if (tokens[index + 1]->type == ID
			|| tokens[index + 1]->type == DQOUTES
			|| tokens[index + 1]->type == SQOUTES)
			return (true);
	}
	return (false);
}
