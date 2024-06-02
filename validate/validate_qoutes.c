/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_qoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:51:29 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/02 20:23:54 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	validate_dqoutes(int index, t_data *data)
{
	t_token	**tokens;

	tokens = data->tokens;
	if (is_cmd(tokens[index]->token_string, data))
		tokens[index]->type = CMDS;
}

bool	validate_qoutes(int index, t_data *data)
{
	t_token	**tokens;

	tokens = data->tokens;
	if (tokens[index]->type == DQOUTES)
		validate_dqoutes(index, data);
	return true;
}