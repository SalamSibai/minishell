// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init_parsing.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/08 11:36:11 by mohammoh          #+#    #+#             */
// /*   Updated: 2024/05/08 14:46:44 by mohammoh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function malloc for each token and set the type of the token 
 * and increments the ctr of the token
 * 
 * @param data 
 */
void	malloc_each_token(int *token_ctr, t_token **tokens, char *buff, 
			int c, size_t len, int *i, int x)
{
	tokens[*token_ctr] = ft_calloc(1, sizeof(t_token));
	tokens[*token_ctr]->token_string = ft_substr(buff, c, len);
	set_type(tokens[*token_ctr]);
	(*token_ctr)++;
	*i += x;
}

/**
 * @brief filling in the tokens stuct 
 * 
 * 
 * @param buff 
 * @param parse 
 */
void	scan(char *buff,t_token **tokens)
{
	int i = 0;
	int c = 0;
	int token_ctr = 0;

	while (buff[i])
	{
		i += ft_skipspaces(buff + i); 
		c = i;
		if ((buff[c] == '>' && buff[c + 1] == '>') || (buff[c] == '<' && buff[c + 1] == '<'))
			malloc_each_token(&token_ctr, tokens, buff, c, 2, &i, 2);
		else if (buff[c] == '>' && buff[c + 1] != '\0' && buff[c + 1] == '|')
			malloc_each_token(&token_ctr, tokens, buff, c, 1, &i, 2);
		else if (buff[c] == '|' || buff[c] == '>' || buff[c] == '<')
			malloc_each_token(&token_ctr, tokens, buff, c, 1, &i, 1);
		else if (buff[c] == '\"')
		{
			while (buff[c] && buff[++c] != '\"')
				;
			if (c > i)
			{
				tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
				tokens[token_ctr]->token_string = ft_substr(buff, i + 1, c - i - 1);
				tokens[token_ctr]->type = DQOUTES;
				token_ctr++;
			}
			i = c + 1;
		}
		else if (buff[c] == '\'')
		{

			while (buff[c] && buff[++c] != '\'')
				;
			if (c > i)
			{
				tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
				tokens[token_ctr]->token_string = ft_substr(buff, i + 1, c - i - 1);
				tokens[token_ctr]->type = SQOUTES;
				token_ctr++;
			}
			i = c + 1;
		}
		else
		{
			while (buff[c] && !ft_isspace(buff[c]) && buff[c] != '|' && buff[c] != '>' && buff[c] != '<' && buff[c] != '\"' && buff[c] != '\'')
				c++;
			if (c > i)
				malloc_each_token(&token_ctr, tokens, buff, i, c - i, &i, 0);
			i = c;
		}
	}
	tokens[token_ctr] = NULL;
}
