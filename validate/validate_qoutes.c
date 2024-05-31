/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_qoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:51:29 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/31 20:55:43 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	validate_dqoutes(t_parsing *parse, int index, t_data *data)
{
	if (is_cmd(parse->tokens[index]->token_string, data))
		parse->tokens[index]->type = CMDS;
}

bool	validate_qoutes(t_parsing *parse, int index, t_data *data)
{
	if (parse->tokens[index]->type == DQOUTES)
		validate_dqoutes(parse, index, data);
	return true;
}