/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/01 17:03:44 by mohammoh         ###   ########.fr       */
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
	int		redir_return;

	ft_memset(&data, 0, sizeof(t_data));
	(void)av;
	if (ac != 1 || !*env)
		return (1);
	set_env(&data, env);
	disable_ctrl_c_echo();
	init_sigaction();
	while (1)
	{
		data.buf = readline("minishell$ ");
		if (!data.buf || ft_strcmp(data.buf, "exit") == 0)
		{
			printf("exit\n");
			exit(1);
		}
		if (ft_strcmp(data.buf, "") == 0)
				continue;
		if (ft_strlen(data.buf) > 0)
			add_history(data.buf);
		if (!validate_syntax(data.buf))
		{
			// printf("im here\n");
			error_handler(INVALID_IN_MSG, INVALID_IN_ER, &data, false);
			// g_exit_status = 127;
			// free(data.buf);
			continue;
		}
		data.tokens = ft_calloc(token_count(data.buf), sizeof(t_token *));
		scan(data.buf, data.tokens);
		data.cmd_ctr = 0;
		if (!validate_tokens(&data))
		{
			error_handler(INVALID_IN_MSG, INVALID_IN_ER, &data, false);
			// free(data.buf);
			// g_exit_status = 127;
			// free tokens
			continue;
		}
		fill_data(&data);
		//need to free the tokens
		// print_data(&data);
		redir_return = check_redirections((&data)->cmds);
		if (redir_return < 0)
		{
			if (redir_return == -1)
				error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, &data, false);
			error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, &data, false);
		}
		execution(&data);
		// g_exit_status = 0;
		// free_data(&data, false);
		// printf("data.buf: %s\n", data.buf);
	}
	cleanup(&data);
	// free_data(&data);
	// return (0);
}
