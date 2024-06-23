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


/*
	execution flow:
		1) create t_data struct and initialize
			- split the PATH into the **path variable
			- store env in **envp
			- initialize and set t_env variable
		2) malloc for and initialize parse_data
		3) scan and fill in lexer & tokens
			- check the tokens, sets the type, and the string that represents the token.
			- increments the lexer (based on the token type)
			- this function also cleans up the string, making sure there are no spaces etc
		4) start filling in **cmd variable from the tokens
		5) if we have pipes:
			- initialzie and set the *pipe varibale from the lexer and the tokenizer
		6) if we have redirections:
			- "> outfile_name" we check the syntax correctness (has a filename or limiter after)
			- if everything is fine, we initialize and store
*/

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
		{
			// tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
			tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
			tokens[token_ctr]->token_string = ft_substr(buff, c, 2);
			set_type(tokens[token_ctr]);
			token_ctr++;
			i += 2;
		}
		else if (buff[c] == '>' && buff[c + 1] != '\0' && buff[c + 1] == '|')
		{
			// tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
			tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
			tokens[token_ctr]->token_string = ft_substr(buff, c, 1);
			set_type(tokens[token_ctr]);
			token_ctr++;
			i += 2;
		}
		else if (buff[c] == '|' || buff[c] == '>' || buff[c] == '<')
		{
			// tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
			tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
			tokens[token_ctr]->token_string = ft_substr(buff, c, 1);
			set_type(tokens[token_ctr]);
			token_ctr++;
			i += 1;
		}
		else if (buff[c] == '\"')
		{

			while (buff[c] && buff[++c] != '\"')
				;
			if (c > i)
			{
				// tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
				tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
				tokens[token_ctr]->token_string = ft_substr(buff, i + 1, c - i - 1);
				tokens[token_ctr]->type = DQOUTES;
				printf("Token string: %s\n", tokens[token_ctr]->token_string);
				printf("string in single qoutes\n");
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
				// tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
				tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
				tokens[token_ctr]->token_string = ft_substr(buff, i + 1, c - i - 1);
				tokens[token_ctr]->type = SQOUTES;
				printf("Token string: %s\n", tokens[token_ctr]->token_string);
				printf("string in single qoutes\n");
				token_ctr++;
			}
			i = c + 1;
		}
		else
		{
			while (buff[c] && !ft_isspace(buff[c]) && buff[c] != '|' && buff[c] != '>' && buff[c] != '<' && buff[c] != '\"' && buff[c] != '\'')
				c++;
			if (c > i)
			{
				// tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
				tokens[token_ctr] = ft_calloc(1, sizeof(t_token));
				tokens[token_ctr]->token_string = ft_substr(buff, i, c - i);
				set_type(tokens[token_ctr]);
				token_ctr++;
				// printf("here");
			}
			i = c;
		}
	}
	printf("token ctr %d\n", token_ctr); 
	// tokens[token_ctr] = NULL;
}
