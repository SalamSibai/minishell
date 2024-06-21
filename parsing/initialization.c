/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:23:56 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/21 14:34:14 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief this function counts the number of commands in the tokens
 * based on the number of pipes except if there was a redirection output 
 * will start with one command and will increment the command number
 * because a pipe could never be the first token and to avoid accessing a null pointer
 * and also because we will always start with one command
 * 
 * based on this number will malloc how many commands structure we have
 *
 * @param tokens 
 * @return number of commands 
 */
int	count_cmds(t_token **tokens)
{
	int	i;
	int	cmd_num;

	if (tokens == NULL && !*tokens)
		return (0);
	i = 1;
	cmd_num = 1;
	while (tokens[i] != NULL)
	{
		if (tokens[i - 1]->type != REDIRECT_OUTPUT && tokens[i]->type == PIPE)
			cmd_num++;
		i++;
	}
	return (cmd_num);
}

/**
 * @brief  function to initialize the commands structure 
 * 
 * @param data 
 */
void	init_cmds(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->cmd_num)
	{
		data->cmds[i] = ft_calloc(1, sizeof(t_cmd));
		data->cmds[i]->fd_in = -1;
		data->cmds[i]->fd_out = -1;
		data->cmds[i]->cmd_path = NULL;
		data->cmds[i]->cmd_str = NULL;
		data->cmds[i]->flag = NULL;
		// data->cmds[i]->args_str = NULL;
		data->cmds[i]->args = NULL;
		i++;
	}
}
