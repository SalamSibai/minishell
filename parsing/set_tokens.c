/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ++4 <mohammoh@student.42abudhabi.ae>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:24:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/27 23:19:07 by ++4              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_type(t_token *token)
{
	if (ft_strcmp(token->token_string, "|") == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->token_string, "-", 1) == 0)
		token->type = FLAG;
	else if (ft_strcmp(token->token_string, "<") == 0)
		token->type = REDIRECT_INPUT;
	else if (ft_strcmp(token->token_string, ">") == 0)
		token->type = REDIRECT_OUTPUT;
	else if (ft_strcmp(token->token_string, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->token_string, ">>") == 0)
		token->type = REDIRECT_APPEND;
	else if (ft_strncmp(token->token_string, "\"", 1) == 0)
		token->type = DQOUTES;
	else if (ft_strncmp(token->token_string, "\'", 1) == 0)
		token->type = SQOUTES;
	else
		token->type = ID;
}

int	token_count(char *av)
{
	int i = -1;
	int token_ctr = 1;
	int in_token = 0;

	if (av[i + 1] == '\0')
		return (token_ctr);
	i = ft_skipspaces(av);
	while (av[i++])
	{
		if (ft_isspace(av[i]))
		{
			if (in_token)
			{
				in_token = 0;
				token_ctr++;
			}
		}
		else if ((av[i] == '|' && av[i + 1] != '|') || (av[i] == '>' && av[i + 1] != '>') ||
					(av[i] == '<' && av[i + 1] != '<'))
		{
			if (in_token)
			{
				in_token = 0;
				token_ctr++;
			}
			token_ctr++;
		}
		else if ((av[i] == '>' && av[i + 1] == '>') || (av[i] == '<' && av[i + 1] == '<'))
		{
			if (in_token)
			{
				in_token = 0;
				token_ctr++;
			}
			token_ctr++;
			i++;
		}
		else if (av[i] == '\"'  || av[i] == '\'')
		{
			if (in_token)
			{
				in_token = 0;
				token_ctr++;
			}
			token_ctr++;
			i++;
		}
		else
		{
			if (!in_token)
				in_token = 1;
		}
	}
	if (in_token)
		token_ctr++;
	return (token_ctr + 2);
}
