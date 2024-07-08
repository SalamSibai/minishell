/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:25 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/07 02:10:21 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->c = 0;
	var->k = 0;
}

/**
 * @brief loops through the given tokens and sets all arguments and
 * redirections linked to that specific command + strjoins all into 1 token
 * also redirection is a linked list that is linked to the command 
 * and when we have a limiter we create a new linked list that is linked to 
 * the redirection linked list so we can always keep the heredoc limiter 
 * the top of the redirection linked list for each command
 * 
 * @param data 
 */
void	set_cmds(t_data *data)
{
	t_token			**tokens;
	t_redirection	*head;
	t_var			var;
	t_list			*new_arg;

	new_arg = NULL;
	tokens = data->tokens;
	init(&var);
	while (var.i < data->cmd_num)
	{
		head = NULL;
		var.k = 0;
		var.c = 0;
		while (tokens[var.j] != NULL && tokens[var.j]->type != PIPE)
		{
			if (check_if_cmd(data, &var, tokens)
				|| check_if_flag(data, &var, tokens, new_arg)
				|| check_if_redir(&var, tokens, &head)
				|| check_if_id(data, &var, tokens, new_arg))
				continue ;
			var.j++;
		}
		data->cmds[var.i++]->redirection = head;
		var.j++;
	}
}
