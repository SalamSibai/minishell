/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:58:53 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/04 04:29:03 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"


static void	set_env(t_data *data, char **env)
{
	data->env = env_init(env);
	data->export_env = export_env_init(data->env);
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
			cleanup(&data);
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		if (ft_strcmp(data.buf, "") == 0)
				continue;
		if (ft_strlen(data.buf) > 0)
			add_history(data.buf);
		if (!validate_syntax(data.buf))
		{
			error_handler(INVALID_IN_MSG, INVALID_IN_ER, &data, false);
			continue;
		}
		data.tokens = ft_calloc(token_count(data.buf), sizeof(t_token *));
		scan(data.buf, data.tokens);
		set_env_and_path(&data, SET);
		data.cmd_ctr = 0;
		if (!validate_tokens(&data))
		{
			free_tokens(&data);
			error_handler(INVALID_IN_MSG, INVALID_IN_ER, &data, false);
			continue;
		}
		fill_data(&data);
	//	print_data(&data);
		redir_return = check_redirections((&data)->cmds);
		if (redir_return < 0)
		{
			if (redir_return == -1)
				error_handler(INPUT_REDIR_ER_MSG, IN_REDIR_ER, &data, false);
			else
				error_handler(OUTPUT_REDIR_ER_MSG, OUT_REDIR_ER, &data, false);
			continue;
		}
		printf("NUMBER OF COMMANDS: %d\n", data.cmd_num);
		execution(&data);
		set_env_and_path(&data, FREE);
		free_cmd(&data);
		g_exit_status = 0;
	}
	cleanup(&data);
	return (0);
}
