/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/08 13:49:16 by mohammoh         ###   ########.fr       */
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
	t_data	data;

	(void)ac;
	(void)av;
	//initlize enviroment variables
	data.cmd_num = 1;
	data.env = env_init(env);
	data.env_var = env_to_str(data.env);
	data.path = set_path(env, &data);
	// int i = 0;
	while (1)
	{
		data.buf = readline("minishell$ ");
		add_history(data.buf);
		if (!data.buf)
		{
			printf("exit\n");
		}
		if (!validate_syntax(data.buf))
		{
			free(data.buf);
			// continue ;
			exit(1);
		}
		data.tokens = ft_safe_malloc(sizeof(t_token *) * token_count(data.buf), "TOKENS");
		scan(data.buf, data.tokens);
		validate_tokens(&data);
		data.tokens = check_expandable_var(data.tokens, data.env);
		data.cmd_num = count_cmds(data.tokens);
		data.cmds = ft_safe_malloc(sizeof(t_cmd *) * data.cmd_num, "CMDS");
		// printf("cmd_num: %d\n", data.cmd_num);
		init_cmds(&data);
		set_cmds(&data);
		// ft_cd(data.cmds[0],data.env); // we need to add the fds as well to know where are we typing these commands 
		// ft_echo(data.cmds[0]);  // we need to add the fds 
		print_data(&data);
		// ft_env(data.env);
		// ft_export(data.cmds[0]->args, data.env);
	
	//execute the input

	//free everything before next itiration
	}
	return (0);
}
