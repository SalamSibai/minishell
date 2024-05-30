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

bool	pasre_setup(t_parsing *parse, int token_ctr)
{
	//t_parsing *parse;


/*
	parse =  ft_safe_malloc(sizeof(t_parsing));
	if (!parse)
		return (false);
*/

	//parse->lexer = ft_safe_malloc(sizeof(t_lexer));
	//if (!parse->lexer)
	//{
	//	//cleanup and free for parse
	//	return (false);
	//}
	// create our lexer and then malloc and setup for our tokens

	if (!(parse->tokens = ft_safe_malloc(sizeof(t_token *) * token_ctr, "TOKENS")))
	{
		//cleanup and free for both lexer and parse
		return (false);
	}
	// printf("Token count: %d\n", token_ctr);
	// parse->tokens[token_ctr] = NULL;
	return (true);
}


/**
 * @brief filling in the tokens stuct 
 * 
 * 
 * @param buff 
 * @param parse 
 */
void	scan(char *buff, t_parsing *parse)
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
			parse->tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
			parse->tokens[token_ctr]->token_string = ft_substr(buff, c, 2);
			set_type(parse->tokens[token_ctr]);
			token_ctr++;
			i += 2;
		}
		else if (buff[c] == '|' || buff[c] == '>' || buff[c] == '<')
		{
			parse->tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
			parse->tokens[token_ctr]->token_string = ft_substr(buff, c, 1);
			set_type(parse->tokens[token_ctr]);
			token_ctr++;
			i += 1;
		}
		else if (buff[c] == '\"')
		{

			while (buff[c] && buff[++c] != '\"')
				;
			if (c > i)
			{
				parse->tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
				parse->tokens[token_ctr]->token_string = ft_substr(buff, i, c - i + 1);
				set_type(parse->tokens[token_ctr]);
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
				parse->tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
				parse->tokens[token_ctr]->token_string = ft_substr(buff, i, c - i + 1);
				set_type(parse->tokens[token_ctr]);
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
				parse->tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
				parse->tokens[token_ctr]->token_string = ft_substr(buff, i, c - i);
				set_type(parse->tokens[token_ctr]);
				token_ctr++;
			}
			i = c;
		}
	}
	parse->tokens[token_ctr] = NULL;
}
