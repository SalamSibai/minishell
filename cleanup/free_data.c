/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:40:49 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/30 22:29:29 by mohammoh         ###   ########.fr       */
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

//MAKE SURE THAT WE RESET THE STDIN AND STDOUT FROM ORIGIN_FDS

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		free(data->tokens[i]->token_string);
		free(data->tokens[i]);
		i++;
	}
	free(data->tokens);
	free(data->pipe->pid);
	free(data->pipe);
	ft_free2d((void **)data->path);
	ft_free2d((void **)data->env_var);
	ft_lstclear(&data->env, (void *)del);
	ft_lstclear(&data->export_env, free);
	i = 0;
	while (data->cmds[i])
	{
		if (data->cmds[i]->cmd_str)
			free(data->cmds[i]->cmd_str);
		if (data->cmds[i]->flag)
			free(data->cmds[i]->flag);
		if (data->cmds[i]->args)
			ft_lstclear(&data->cmds[i]->args, (void *)del);
		if (data->cmds[i]->redirection)
			redir_clear(&data->cmds[i]->redirection);
		if (data->cmds[i]->cmd_with_flag)
			ft_free2d((void **)data->cmds[i]->cmd_with_flag);
		i++;
	}
	ft_free2d((void **)data->cmds);
	//free(data->cmds);
	//free(data);
}
