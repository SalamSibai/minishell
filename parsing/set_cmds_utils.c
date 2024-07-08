/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:08:08 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 21:08:11 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	check_if_cmd(t_data *data, t_var *var, t_token **tokens)
{
	if (tokens[var->j]->type == CMDS)
	{
		data->cmds[var->i]->cmd_str = ft_strdup(tokens[var->j]->token_string);
		var->j++;
		return (true);
	}
	return (false);
}

bool	check_if_flag(t_data *data, t_var *var, t_token **t, t_list *new_arg)
{
	if (t[var->j]->type == FLAG)
	{
		if (var->k == 0)
		{
			data->cmds[var->i]->flag
				= ft_lstnew(ft_strdup(t[var->j]->token_string));
			var->k = 1;
		}
		else
		{
			new_arg = ft_lstnew(ft_strdup(t[var->j]->token_string));
			ft_lstadd_back(&data->cmds[var->i]->flag, new_arg);
		}
		var->j++;
		return (true);
	}
	return (false);
}

bool	check_if_id(t_data *data, t_var *var, t_token **tokens, t_list *new_arg)
{
	if (tokens[var->j]->type == ID)
	{
		if (var->c == 0)
		{
			data->cmds[var->i]->args
				= ft_lstnew(ft_strdup(tokens[var->j]->token_string));
			var->c = 1;
		}
		else
		{
			new_arg = ft_lstnew(ft_strdup(tokens[var->j]->token_string));
			ft_lstadd_back(&data->cmds[var->i]->args, new_arg);
		}
		var->j++;
		return (true);
	}
	return (false);
}

bool	check_if_redir(t_var *var, t_token **tokens, t_redirection **head)
{
	if (tokens[var->j]->type == REDIRECT_INPUT)
		return (redir_add_back(head, redir_new(REDIRECT_INPUT, NULL, NULL)),
			var->j++, true);
	else if (tokens[var->j]->type == REDIRECT_OUTPUT
		|| tokens[var->j]->type == REDIRECT_APPEND)
	{
		redir_add_back(head, redir_new(tokens[var->j]->type, NULL, NULL));
		return (var->j++, true);
	}
	else if (tokens[var->j]->type == HEREDOC)
	{
		redir_add_back(head, redir_new(HEREDOC, NULL, NULL));
		return (var->j++, true);
	}
	else if (tokens[var->j]->type == FILE_NAME)
	{
		redir_last(*head)->file_name = ft_strdup(tokens[var->j]->token_string);
		return (var->j++, true);
	}
	else if (tokens[var->j]->type == LIMITER)
	{
		redir_last(*head)->limiter = ft_strdup(tokens[var->j]->token_string);
		return (var->j++, true);
	}
	return (false);
}
