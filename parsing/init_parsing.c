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
	//parse->tokens[token_ctr] = NULL;
	return (true);
}

	/*
		go through the input (av)
			1- until there's a space, tab, etc... 
			2- once a set of characters are grouped, send them to set token
				a- set token mallocs for the token
				b- sets the type of the token
	gradually fill in tokens within the tokens struct
	*/

/// @brief 
/// @param buff 
/// @param parse 
void	scan(char *buff, t_parsing *parse)
{
	int i;
	int c;
	int token_ctr;

	token_ctr = 0;
	i = 0;
	while (buff[i])
	{
		printf("i is %d\n", i);
		i = ft_skipspaces(buff + i);
		c = i;
		printf("buff of i is: %c\n", buff[i]);
		while (!ft_isspace(buff[c]) && buff[c])
			c++;
		//i is the start of the string, c-1 is the end of the string before a space
		if (c > i)
		{
			printf("found char [%c]\n", buff[i]);
			parse->tokens[token_ctr] = ft_safe_malloc(sizeof(t_token), "Token data");
			parse->tokens[token_ctr]->token_string = ft_substr(buff, i, c - 1);
			token_ctr++;
		}
		i += (c + 1);
		printf("i is %d and the char is %c\n", i, buff[i]);
	}
	parse->tokens[token_ctr] = NULL;

		// while (av[i] && !ft_isspace(av[i]))
		// {
		// 	str[c++] = av[i++];
		// 	//NOTE: CHECK IF USERS ARE ALLOWED TO SEND MULTIPLE COMMANDS BETWEEN TWO ""
		// 	//IF YES, WE MUST HAVE AN OUTER LOOP TOO TO STORE EACH TOKEN WITHIN ONE VARIABLE SENT TO MAIN
		// }
		// parse->tokens[token_ctr] = set_token(str);
		// printf("Token: %s\n", parse->tokens[token_ctr]->token_string);
		/*
			if (!parse->tokens[token_ctr])
				free, cleanup, empty, exit
		*/
		//empty str;

}



// int main ()
// {
// 	//check scan function
// 	//check set_token function
	
// 	char *av[] = {"ls", "-l", "echo", "hello", "world", NULL};
// 	t_parsing *parse = NULL;

// 	scan(av, parse);
// }