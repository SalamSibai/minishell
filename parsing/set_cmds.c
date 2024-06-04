/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:25 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/04 21:33:00 by mohammoh         ###   ########.fr       */
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
	int		i;
	int		j;
	int 	c;
	
	tokens = data->tokens;
	i = 0;
	j = 0;
	while (i < data->cmd_num)
	{
		c = 0;
		while (tokens[j] != NULL && tokens[j]->type != PIPE)
		{
			if (tokens[j]->type == CMDS)
			{
				data->cmds[i]->cmd_str = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == FLAG)
			{ 
				data->cmds[i]->cmd_str = ft_strjoin(data->cmds[i]->cmd_str, " ");
				data->cmds[i]->cmd_str = ft_strjoin(data->cmds[i]->cmd_str, tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == REDIRECT_INPUT)
			{
				data->cmds[i]->redirection->type = tokens[j]->type;
				data->cmds[i]->redirection->fd = 0;
				j++;
			}
			else if (tokens[j]->type == REDIRECT_OUTPUT)
			{
				data->cmds[i]->redirection->type = tokens[j]->type;
				data->cmds[i]->redirection->fd = 1;
				j++;
			}
			else if (tokens[j]->type == HEREDOC)
			{
				data->cmds[i]->redirection->type = tokens[j]->type;
				data->cmds[i]->redirection->fd = 1;
				j++;
			}
			else if (tokens[j]->type == FILE_NAME)
			{
				data->cmds[i]->redirection->file_name = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == LIMITER)
			{
				data->cmds[i]->redirection->limiter = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == ID)
			{
				if (c == 0)
				{
					data->cmds[i]->args_str = ft_strdup(tokens[j]->token_string);
					c = 1;
				}
				else
				{
					data->cmds[i]->args_str = ft_strjoin(data->cmds[i]->args_str, " ");
					data->cmds[i]->args_str = ft_strjoin(data->cmds[i]->args_str, tokens[j]->token_string);
				}
				j++;
			}
			else if (tokens[i]->type == FILE_NAME)
			{
				data->cmds[i]->redirection->file_name = ft_strdup(tokens[j]->token_string);
				j++;
			}
			else
				j++;
		}
		i++;
		j++;
		
	}
}
