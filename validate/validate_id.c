/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:02:50 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/30 22:21:16 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// bool	check_access(char **path, t_token token)
// {
// 	if (access(*path, F_OK) == 0)
// 	{
// 		if (access(*path, X_OK) == 0)
// 			return (true);
// 		else
// 			return (false);
// 	}
// }

/// @brief validates the ID token
/// @param parse the parse struct
/// @param index the index of the ID we are checking
/// @return true if passed token is valid
bool	validate_id(t_parsing *parse, int index) // NOTE: add t_data data to get the path then we check if its an executable
{
	if (index == 0) // WE CAN CHECK IF ITS AN EXECUTABLE OR NOT
		parse->tokens[index]->type = CMDS;
	else
	{
		if (parse->tokens[index - 1]->type == REDIRECT_INPUT
			|| parse->tokens[index - 1]->type == REDIRECT_APPEND
			|| parse->tokens[index - 1]->type == REDIRECT_OUTPUT)
				parse->tokens[index]->type = FILE_NAME;
		else if (parse->tokens[index - 1]->type == HEREDOC)
			parse->tokens[index]->type = LIMITER;
		else
			parse->tokens[index]->type = CMDS;
	}
	return (true);
}
