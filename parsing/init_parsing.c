/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:11 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/07 02:42:18 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_double_quotes(int *i, int *token_ctr, t_token **tokens, char *buff)
{
	int c;

	c = *i;
	while (buff[c] && buff[++c] != '\"')
		;
	if (c > *i)
		malloc_qoutes_token(tokens, token_ctr, buff, *i + 1, c - *i - 1, DQOUTES, true);
	*i = c + 1;
}


void	handle_single_quotes(int *i, int *token_ctr, t_token **tokens, char *buff)
{
	int	c;

	c = *i;
	while (buff[c] && buff[++c] != '\'')
		;
	if (c > *i)
	{
		malloc_qoutes_token(tokens, token_ctr, buff, *i + 1, c - *i - 1, SQOUTES, false);
		*i = c + 1;
	}
	else
		*i = c + 1;
}

void	handle_other_chars(int *i, int *token_ctr, t_token **tokens, char *buff)
{
	int c;

	c = *i;
	while (buff[c] && !ft_isspace(buff[c]) && buff[c] != '|' && buff[c] != '>'
		&& buff[c] != '<' && buff[c] != '\"' && buff[c] != '\'')
		c++;
	if (c > *i)
		malloc_each_token(token_ctr, tokens, buff, *i, c - *i, i, 0);
	*i = c;
}

void	handle_special_chars(int *i, int *token_ctr, t_token **tokens, char *buff)
{
	int	c;

	c = *i;
	if ((buff[c] == '>' && buff[c + 1] == '>') || (buff[c] == '<' && buff[c + 1] == '<'))
		malloc_each_token(token_ctr, tokens, buff, c, 2, i, 2);
	else if (buff[c] == '>' && buff[c + 1] != '\0' && buff[c + 1] == '|')
		malloc_each_token(token_ctr, tokens, buff, c, 1, i, 2);
	else if (buff[c] == '|' || buff[c] == '>' || buff[c] == '<')
		malloc_each_token(token_ctr, tokens, buff, c, 1, i, 1);
}

void	scan(char *buff, t_token **tokens)
{
	int	i;
	int	token_ctr;

	i = 0;
	token_ctr = 0;
	while (buff[i])
	{
		i += ft_skipspaces(buff + i);
		if (buff[i] == '\"')
			handle_double_quotes(&i, &token_ctr, tokens, buff);
		else if (buff[i] == '\'')
			handle_single_quotes(&i, &token_ctr, tokens, buff);
		else if (buff[i] == '|' || buff[i] == '>' || buff[i] == '<')
			handle_special_chars(&i, &token_ctr, tokens, buff);
		else
			handle_other_chars(&i, &token_ctr, tokens, buff);
		}
	tokens[token_ctr] = NULL;
}
