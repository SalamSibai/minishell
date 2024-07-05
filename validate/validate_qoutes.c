/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_qoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:24:46 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/05 05:51:31 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	validate_dquotes(int index, t_data *data)
{
	t_token	**tokens;
	char	**dquoted_strs;
	int		i;

	i = 0;
	dquoted_strs = ft_split(tokens[index]->token_string, ' ');
	while (dquoted_strs[i] != NULL)
		i++;

	/*while (tokens[index]->token_string[i] != '\0')
	{
		if (tokens[index]->token_string[i] == '$')
		{
			temp = ft_substr(tokens[index]->token_string, i, ft_strlen(tokens[index]->token_string));
			
			printf("temp len is: %d\n", (int)temp_len);
			printf("temp is: %s\n", temp);
			printf("rest is: %s\n", rest_str);
			//check the string till where there's a space and store that somewhere
			free(temp);
		}
		i ++;
	}*/

/*
	if (ft_strcmp(tokens[index]->token_string, "|") == 0)
		tokens[index]->type = PIPE;
	else if ((is_cmd(tokens[index]->token_string, data) && index == 0)
		|| tokens[index - 1]->type == PIPE)
		tokens[index]->type = CMDS;
	else if (tokens[index - 1]->type == REDIRECT_INPUT
		|| tokens[index - 1]->type == REDIRECT_APPEND
		|| tokens[index - 1]->type == REDIRECT_OUTPUT)
		tokens[index]->type = FILE_NAME;
	else if (tokens[index - 1]->type == HEREDOC)
		tokens[index]->type = LIMITER;
	else if (tokens[index - 1]->type == CMDS)
		tokens[index]->type = ID;
	else
		tokens[index]->type = ID;
*/
}


int	validate_quotes(int index, t_data *data)
{
	if (data->tokens[index]->type == DQOUTES)
		return (validate_dquotes(index, data));
	return (index + 1);
}
