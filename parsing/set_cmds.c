/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:16:25 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/03 01:11:09 by mohammoh         ###   ########.fr       */
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
	int	i;
	int	j;
	
	tokens = data->tokens;
	i = 0;
	j = 0;
	while (i < data->cmd_num)
	{
		while (tokens[j] != NULL && tokens[j]->type != PIPE)
		{
			if (tokens[j]->type == CMDS)
			{
				data->cmd[i]= ft_strdup(tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == FLAG)
			{
				data->cmd[i] = ft_strjoin(data->cmd[i], " ");
				data->cmd[i] = ft_strjoin(data->cmd[i], tokens[j]->token_string);
				j++;
			}
			else if (tokens[j]->type == REDIRECT_INPUT)
			{
				data->cmd[i]->redirection->type = tokens[j]->type;
				data->cmd[i]->redirection->fd = 0;
				j++;
			}
			else if (tokens[j]->type == REDIRECT_OUTPUT)
			{
				data->cmd[i]->redirection->type = tokens[j]->type;
				data->cmd[i]->redirection->fd = 1;
				j++;
			}
			else if (tokens[j]->type == HEREDOC)
			{
				data->cmd[i]->redirection->type = tokens[j]->type;
				data->cmd[i]->redirection->fd = 1;
				j++;
			}
			else if (tokens[j]->type == FILE_NAME)
			{
				data->cmd[i]->redirection->file_name = ft_strdup(tokens[j]->token_string);
				j++;
			}
		}
		i++;
		j++;
	}
	
}
