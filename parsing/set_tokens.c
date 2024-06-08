/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:24:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/08 21:29:34 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_type(t_token *token)
{
	//strcmp
	// printf("Token string: %s\n", token->token_string);
	if (ft_strcmp(token->token_string, "|") == 0)
	{
		token->type = PIPE;
		// printf("pipe\n");
	}
	else if (ft_strncmp(token->token_string, "-", 1) == 0)
	{
		token->type = FLAG;
		// printf("flag\n");
	}
	else if (ft_strcmp(token->token_string, "<") == 0)
	{
		token->type = REDIRECT_INPUT;
		// printf("redirect input\n");
	}
	else if (ft_strcmp(token->token_string, ">") == 0)
	{
		token->type = REDIRECT_OUTPUT;
		// printf("redirect output\n");
	}
	else if (ft_strcmp(token->token_string, "<<") == 0)
	{
		token->type = HEREDOC;
		// printf("heredoc\n");
	}
	else if (ft_strcmp(token->token_string, ">>") == 0)
	{
		token->type = REDIRECT_APPEND;
		// printf("redirect append\n");
	}
	else if (ft_strncmp(token->token_string, "\"", 1) == 0)
	{
		//loop until we find the next "
		token->type = DQOUTES;
		// printf("string in double qoutes\n");
	}
	else if (ft_strncmp(token->token_string, "\'", 1) == 0)
	{
		//loop until we find the next "
		token->type = SQOUTES;
		// printf("string in single qoutes\n");
	}
	else
	{
		token->type = ID;
		// printf("ID\n");
	}
	// printf("token type %d\n", token->type);
	//$ env variables
	//$? what
}

int	token_count(char *av)
{
	int i = -1;
	int token_ctr = 0;
	int in_token = 0;

	i = ft_skipspaces(av);
	while (av[++i])
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
	// printf("Token count: %d\n", token_ctr);
	return (token_ctr + 1);
}
