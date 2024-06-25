/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:25 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/25 16:58:49 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	t_list			*new_arg;
	t_redirection	*head;
	int				i;
	int				j;
	int 			c;
	
	i = 0;
	j = 0;
	tokens = data->tokens;
	while (i < data->cmd_num)
	{
		c = 0;
		head = NULL;
		while (tokens[j] != NULL && tokens[j]->type != PIPE)
		{
			if (tokens[j]->type == CMDS)
			{
				data->cmds[i]->cmd_str = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == FLAG)
			{ 
				data->cmds[i]->flag = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == REDIRECT_INPUT)
			{
				redir_add_back(&head, redir_new(REDIRECT_INPUT, NULL, NULL));
				j++;
			}
			else if (tokens[j]->type == REDIRECT_OUTPUT || tokens[j]->type == REDIRECT_APPEND)
			{
				redir_add_back(&head, redir_new(tokens[j]->type, NULL, NULL));
				j++;
			}
			else if (tokens[j]->type == HEREDOC)
			{
				redir_add_back(&head, redir_new(HEREDOC, NULL, NULL));
				j++;
			}
			else if (tokens[j]->type == FILE_NAME)
			{
				redir_last(head)->file_name = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == LIMITER)
			{
				redir_last(head)->limiter = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == ID)
			{
				if (c == 0)
				{
					data->cmds[i]->args = ft_lstnew(tokens[j]->token_string);
					c = 1;
				}
				else
				{
					new_arg = ft_lstnew(tokens[j]->token_string);
					ft_lstadd_back(&data->cmds[i]->args, new_arg);
				}
				j++;
			}
			else
				j++;
		}
		data->cmds[i]->redirection = head;
		i++;
		j++;
	}
}
