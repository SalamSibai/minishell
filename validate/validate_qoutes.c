/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_qoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:24:46 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/06 15:27:41 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	validate_dqoutes(int index, t_data *data)
{
	t_token	**tokens;

	tokens = data->tokens;
	if ((index == 0) || tokens[index - 1]->type == PIPE)
		tokens[index]->type = CMDS;
	else if (tokens[index - 1]->type == REDIRECT_INPUT
		|| tokens[index - 1]->type == REDIRECT_APPEND
		|| tokens[index - 1]->type == REDIRECT_OUTPUT)
		tokens[index]->type = FILE_NAME;
	else if (tokens[index - 1]->type == HEREDOC)
		tokens[index]->type = LIMITER;
	else if (tokens[index - 1]->type == CMDS)
		tokens[index]->type = ID;
	else
		tokens[index]->type = ID;
}

bool	validate_qoutes(int index, t_data *data)
{
	validate_dqoutes(index, data);
	return (true);
}
