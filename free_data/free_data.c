/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:40:49 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/10 16:59:17 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
* 	1) free tokens
		*tokens_string to be free
* 	2) free cmds
		*cmd_str to be free
		*cmd flag to be free if not null 
		*args linked list to be free if any
		*redirection linked list to be free if any
			- file_name to be free
			- limiter to be free
			then free the redirection
* 	3) free buf
*/

void	free_data(t_data *data)
{
	int				i;
	t_redirection	*tmp;

	i = 0;
	while (data->tokens[i])
	{
		free(data->tokens[i]->token_string);
		free(data->tokens[i]);
		i++;
	}
	free(data->tokens);
	i = 0;
	while (data->cmds[i])
	{
		free(data->cmds[i]->cmd_str);
		if (data->cmds[i]->flag)
			free(data->cmds[i]->flag);
		// if (data->cmds[i]->args)
		// 	ft_lstclear(&data->cmds[i]->args, (void *)del);
		if (data->cmds[i]->redirection)
		{
			while (data->cmds[i]->redirection)
			{
				if (data->cmds[i]->redirection->next)
					tmp = data->cmds[i]->redirection->next;
				if (data->cmds[i]->redirection->file_name)
					free(data->cmds[i]->redirection->file_name);
				if (data->cmds[i]->redirection->limiter)
					free(data->cmds[i]->redirection->limiter);
				free(data->cmds[i]->redirection);
				data->cmds[i]->redirection = tmp;
			}
		}
		free(data->cmds[i]);
		i++;
	}

	free(data->buf);
}