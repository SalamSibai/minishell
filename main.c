/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/23 22:06:12 by ssibai           ###   ########.fr       */
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

bool	make_pipes(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pipe(p->fd[i]) == -1)
			return (false);
		i ++;
		ft_putstr_fd("pipe open\n", 1);
	}
	return (true);
}

void	alloc_pids(t_data *data)
{
	data->pipe->pid = (int *)malloc(data->cmd_num * sizeof(int));
	if (!data->pipe->pid)
		return ;
		//error_handler("Malloc: no space for pids", 1, d, p);
}

static void	set_env(t_data *data, char **env)
{
	data->env = env_init(env);
	data->export_env = export_env_init(data->env);
	data->env_var = env_to_str(data->env);
	data->path = set_path(env, data);
}

static void	fill_data(t_data *data)
{
	data->cmd_ctr = 0;
	data->tokens = check_expandable_var(data->tokens, data->env);
	data->cmd_num = count_cmds(data->tokens);
	data->cmds = ft_calloc(data->cmd_num + 1, sizeof(t_cmd *));
	data->pipe = ft_calloc(1, sizeof(t_pipe));
	init_cmds(data);
	set_cmds(data);
}

int main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;

	set_env(&data, env);

	///
	// data.buf = "echo hello world > df > 1 < 2 | echo 'hello world' << f > 3 > 4 > 7 | ls -l ";
	while (1)
	{
		data.buf = readline("minishell$ ");
		add_history(data.buf);
		if (!data.buf)
		{
			printf("exit\n");
			exit(3);
		}
		if (!validate_syntax(data.buf))
		{
			free(data.buf);
			// continue;
		}
		// data.tokens = ft_safe_malloc(sizeof(t_token *) * token_count(data.buf), "TOKENS");
		data.tokens = ft_calloc(token_count(data.buf), sizeof(t_token *));
		scan(data.buf, data.tokens);
		data.cmd_ctr = 0;
		if (!validate_tokens(&data))
			return 0;
			// break ;
		fill_data(&data);
		//need to free the tokens
		//print_data(&data);
		//function that checks for redirections within each cmd
		check_redirections((&data)->cmds);
		execution(&data);
		//exec_builtin((&data)->cmds[0], &data);
		// execute_cmds(&data);
		
	//execute the input

	// free everything before next itiration
	}
	// free_data(&data);
	// return (0);
}
