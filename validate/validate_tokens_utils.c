/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:02:03 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 22:31:58 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_id(t_data *data, int i, t_token **tokens)
{
	if (tokens[i]->type == ID)
	{
		if (!validate_id(i, data))
			return (-1);
		return (1);
	}
	return (0);
}

int	if_pipe(t_data *data, int i, t_token **tokens)
{
	if (tokens[i]->type == PIPE)
	{
		if (!validate_pipe(tokens, i))
			return (-1);
		data->cmd_num++;
		data->cmd_ctr = 0;
		return (1);
	}
	return (0);
}

int	if_input(int i, t_token **tokens)
{
	if (tokens[i]->type == REDIRECT_INPUT
		|| tokens[i]->type == HEREDOC)
	{
		if (!validate_input_redirection(tokens, i))
			return (-1);
		return (1);
	}
	return (0);
}

int	if_output(int i, t_token **tokens)
{
	if (tokens[i]->type == REDIRECT_OUTPUT
		|| tokens[i]->type == REDIRECT_APPEND)
	{
		if (!validate_output_redirection(tokens, i))
			return (-1);
		return (1);
	}
	return (0);
}

int	if_quote_or_dquote(int i, t_token **tokens, t_data *data)
{
	if (tokens[i]->type == DQOUTES || tokens[i]->type == SQOUTES)
	{
		if (!validate_qoutes(i, data))
			return (-1);
		return (1);
	}
	return (0);
}
