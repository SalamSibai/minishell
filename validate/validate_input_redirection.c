/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:23:52 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/05 05:47:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates input redirection
/// @param parse the parse struct
/// @param index the index of the token
/// @return true if the token is valid
bool	validate_input_redirection(t_token **tokens, int index)
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
