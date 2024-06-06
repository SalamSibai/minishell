/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:25 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/06 16:20:24 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/// @brief loops through the given tokens and sets all arguments and
///			and redirections linked to that specific command
///			+ strjoins all into 1 token
/// @param data 
void	set_cmds(t_data *data)
{
	t_token **tokens;
	t_list	*new_arg;
	int		i;
	int		j;
	int 	c;
	int		r;
	
	tokens = data->tokens;
	i = 0;
	j = 0;
	r = 0;
	while (i < data->cmd_num)
	{
		c = 0;
		r = 0;
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
				// data->cmds[i]->cmd_str = ft_strjoin(data->cmds[i]->cmd_str, " ");
				// data->cmds[i]->cmd_str = ft_strjoin(data->cmds[i]->cmd_str, tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == REDIRECT_INPUT)
			{
				data->cmds[i]->redirection[r]->type = tokens[j]->type;
				data->cmds[i]->redirection[r]->fd = 0;
				j++;
			}
			else if (tokens[j]->type == REDIRECT_OUTPUT || tokens[j]->type == REDIRECT_APPEND)
			{
				data->cmds[i]->redirection[r]->type = tokens[j]->type;
				data->cmds[i]->redirection[r]->fd = 1;
				j++;
			}
			else if (tokens[j]->type == HEREDOC)
			{
				data->cmds[i]->redirection[r]->type = tokens[j]->type;
				data->cmds[i]->redirection[r]->fd = 1;
				j++;
			}
			else if (tokens[j]->type == FILE_NAME)
			{
				printf("im here for some reason\n\n\n\n");
				printf("token %s\n", tokens[j]->token_string);
				data->cmds[i]->redirection[r]->file_name = ft_strdup(tokens[j]->token_string);
				j++;
				r++;
			}
			else if (tokens[j]->type == LIMITER)
			{
				data->cmds[i]->redirection[r]->limiter = ft_strdup(tokens[j]->token_string);
				j++;
				r++;
			}
			else if (tokens[j]->type == ID)
			{
				if (c == 0)
				{
					// data->cmds[i]->args_str = ft_strdup(tokens[j]->token_string);
					data->cmds[i]->args = ft_lstnew(tokens[j]->token_string);
					c = 1;
				}
				else
				{
					new_arg = ft_lstnew(tokens[j]->token_string);
					ft_lstadd_back(&data->cmds[i]->args, new_arg);
					
					// data->cmds[i]->args_str = ft_strjoin(data->cmds[i]->args_str, " ");
					// data->cmds[i]->args_str = ft_strjoin(data->cmds[i]->args_str, tokens[j]->token_string);
				}
				j++;
			}
			else
				j++;
		}
		i++;
		j++;
		
	}
}
