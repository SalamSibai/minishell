/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:23:52 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/30 19:25:52 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief validates input redirection
/// @param parse the parse struct
/// @param index the index of the token
/// @return true if the token is valid
bool	validate_input_redirection(t_parsing *parse, int index)
{
	if (parse->tokens[index + 1] != NULL)
	{
		if (parse->tokens[index + 1] == ID)
			return (true);
	}
	return (false);
}
