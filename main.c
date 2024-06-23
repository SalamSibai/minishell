/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/24 00:43:35 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

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
	while (1)
	{
		data.buf = NULL;
		data.buf = readline("minishell$ ");
		if (!data.buf )
		{
			printf("exit\n");
			exit(1);
		}
		if (ft_strcmp(data.buf, "") == 0)
				return (1);
		if (ft_strlen(data.buf) > 0)
			add_history(data.buf);
		if (!validate_syntax(data.buf))
		{
			free(data.buf);
			// continue;
		}
		data.tokens = ft_calloc(token_count(data.buf), sizeof(t_token *));
		scan(data.buf, data.tokens);
		data.cmd_ctr = 0;
		if (!validate_tokens(&data))
			return 0;
		fill_data(&data);
		//need to free the tokens
		// print_data(&data);
		check_redirections((&data)->cmds);
		execution(&data);
		// printf("data.buf: %s\n", data.buf);
	}
	// free_data(&data);
	// return (0);
}
