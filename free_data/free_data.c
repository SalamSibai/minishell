/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:40:49 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/13 22:31:01 by mohammoh         ###   ########.fr       */
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
	
	i = 0;
	while (data->tokens[i])
	{
		free(data->tokens[i]->token_string);
		free(data->tokens[i]);
		i++;
	}
	free(data->tokens);
	ft_free2d((void **)data->path);
	ft_free2d((void **)data->env_var);
	ft_lstclear(&data->env, (void *)del);
	i = 0;
	while (data->cmds[i])
	{
		if (data->cmds[i]->cmd_str)
			free(data->cmds[i]->cmd_str);
		if (data->cmds[i]->flag)
			free(data->cmds[i]->flag);
		if (data->cmds[i]->args_str)
			free(data->cmds[i]->args_str);
		if (data->cmds[i]->args)
			ft_lstclear(&data->cmds[i]->args, (void *)del);
		if (data->cmds[i]->redirection)
			redir_clear(&data->cmds[i]->redirection);
		i++;
	}
	ft_free2d((void **)data->cmds);
}
