/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/28 16:05:47 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

int main(int ac, char **av, char **env)
{
	t_parsing	*parse = NULL;
	t_data		data;

	(void)ac;
	(void)av;
	//initlize enviroment variables
	data.env = env_init(env);
	data.env_var = env_to_str(data.env);
	int i = 0;
	while (1)
	{
		data.buf = readline("minishell$ ");
		add_history(data.buf);
		if (!data.buf)
		{
			printf("exit\n");
			break ;
		}
		if (!validate_syntax(data.buf))
		{
			free(data.buf);
			continue ;
		}
	//initialize expansion variables
	//initialize the path
	//check syntax error
	//parse the input

	pasre_setup(parse, token_count(data.buf));
	scan(data.buf, parse);
	//validate the input //pre validation
	//execute the input
	}
	return (0);
}

