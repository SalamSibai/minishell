/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_qoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:51:29 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/10 16:50:17 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



//we just add quotes to the same function that we are using for validating the ID
void	validate_dqoutes(int index, t_data *data)
{
	t_token	**tokens;

	tokens = data->tokens;
	if (is_cmd(tokens[index]->token_string, data) || index == 0 || tokens[index - 1]->type == PIPE)
		tokens[index]->type = CMDS;
	else if (tokens[index - 1]->type == REDIRECT_INPUT
			|| tokens[index - 1] ->type == REDIRECT_APPEND
			|| tokens[index - 1]->type == REDIRECT_OUTPUT) //|| tokens[index - 1]->type == FLAG// we need toc check if the file exist
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
	// t_token	**tokens;

	// tokens = data->tokens;
	// if (tokens[index]->type == DQOUTES)
	validate_dqoutes(index, data);
	return true;
}