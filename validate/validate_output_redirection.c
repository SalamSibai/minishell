/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_output_redirection.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:30:29 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/30 19:32:43 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates output redirection
/// @param parse the parsing struct
/// @param index index of token
/// @return true if the token is valid
bool	validate_output_redirection(t_parsing *parse, int index)
{
	if (parse->tokens[index + 1] != NULL)
	{
		if (parse->tokens[index + 1]->type == ID)
			return (true);
	}
	return (false);
}
