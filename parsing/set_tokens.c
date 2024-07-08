/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:24:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/01 20:22:47 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_type(t_token *token)
{
	token->expandable = true;
	if (ft_strcmp(token->token_string, "|") == 0)
		token->type = PIPE;
	else if ((ft_strncmp(token->token_string, "-", 1) == 0)
		&& !(ft_strncmp(token->token_string, "-", 2) == 0))
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
	int	i;
	int	token_ctr;
	int	in_token;

	i = -1;
	token_ctr = 0;
	in_token = 0;
	if (av[i + 1] == '\0')
		return (token_ctr);
	i = ft_skipspaces(av);
	while (av[i++])
		itir_tokens(&token_ctr, &in_token, av, &i);
	if (in_token)
		token_ctr++;
	return (token_ctr + 2);
}
