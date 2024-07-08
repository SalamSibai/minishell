/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:57:29 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 21:58:16 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_in_v(t_cmd *cmd, t_data *data, int i, bool *cmd_exist)
{
	if (*cmd_exist)
	{
		close_all_fds(3);
		execve(cmd->cmd_path, cmd->cmd_with_flag, data->env_var);
	}
	else
	{
		close_fds(data, i, true);
		free_cmd(data);
		set_env_and_path(data, FREE);
		error_handler(CMD_ER_MSG, CMD_ER, data, true);
	}
}
