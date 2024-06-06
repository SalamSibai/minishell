/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:07:27 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/06 16:27:34 by mohammoh         ###   ########.fr       */
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

	if (tokens == NULL)
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
 * @brief 
 * 
 * 
 * @param tokens 
 * @param start_index 
 * @return 
 */
int		count_redir_in_cmd(t_token **tokens, int *start_index)
{
	int	i;
	int	num_of_redir;

	if (tokens == NULL)
		return (0);

	i = *start_index;
	num_of_redir = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type == PIPE )
			break;
		if (tokens[i]->type == REDIRECT_OUTPUT || tokens[i]->type == REDIRECT_APPEND 
			|| tokens[i]->type == REDIRECT_INPUT || tokens[i]->type == HEREDOC
			|| tokens[i]->type == FILE_NAME) // NEED TO CONFIRM THIS IS ASWELL 
			num_of_redir++;
		i++;
	}
	*start_index = i + 1;
	return (num_of_redir + 1);
}
