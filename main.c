/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/08 21:29:59 by mohammoh         ###   ########.fr       */
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

static void	set_env(t_data *data, char **env)
{
	data->env = env_init(env);
	data->env_var = env_to_str(data->env);
	data->path = set_path(env, data);
}

static void	fill_data(t_data *data)
{
	data->tokens = check_expandable_var(data->tokens, data->env);
	data->cmd_num = count_cmds(data->tokens);
	data->cmds = ft_safe_malloc(sizeof(t_cmd *) * data->cmd_num, "CMDS");
	init_cmds(data);
	set_cmds(data);
}

int main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;

	set_env(&data, env);
	while (1)
	{
		data.buf = readline("minishell$ ");
		add_history(data.buf);
		if (!data.buf)
		{
			printf("exit\n");
			exit(1);
		}
		if (!validate_syntax(data.buf))
		{
			free(data.buf);
			continue;
		}
		data.tokens = ft_safe_malloc(sizeof(t_token *) * token_count(data.buf), "TOKENS");
		scan(data.buf, data.tokens);
		if (!validate_tokens(&data))
			break ;
		fill_data(&data);
		//need to free the tokens
		print_data(&data);
		// ft_cd(data.cmds[0],data.env); // we need to add the fds as well to know where are we typing these commands 
		// ft_echo(data.cmds[0]);  // we need to add the fds 
		// ft_export(data.cmds[0]->args, data.env);
		// ft_env(data.env);
	//execute the input

	//free everything before next itiration
	}
	return (0);
}
