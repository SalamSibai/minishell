/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_qoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:51:29 by ssibai            #+#    #+#             */
/*   Updated: 2024/05/31 20:09:52 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	validate_dqoutes(t_parsing *parse, int index, t_data *data)
{
	char	*trim_qoute;

	if (is_cmd(trim_qoute, data))
	{
		parse->tokens[index]->token_string = trim_qoute;
		parse->tokens[index]->type = CMDS;
	}
}

bool	validate_qoutes(t_parsing *parse, int index, t_data *data)
{
	if (parse->tokens[index]->type == DQOUTES)
		validate_dqoutes(parse, index, data);
	return true;
}