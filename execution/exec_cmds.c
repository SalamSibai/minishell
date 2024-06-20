/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/20 17:06:11 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 */
void	exec_cmd(t_cmd *cmd, t_data *data, int i, int j)
{
	(void)i;
	(void)j;
	redirect_fds(data, cmd, i, j);
	if (is_builtin(cmd->cmd_str))
		exec_builtin(cmd, data);
	else
	{
		
	}
}

/**
 * @brief this function will execute the commands based on the type of command
 * 
 * @param data
 */
void	execution(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->cmd_num > 1)
	{
		while (data->cmds[i] != NULL && data->cmds[i]->cmd_str != NULL)
		{

			exec_cmd(data->cmds[i], data, i, j);
			i++;
			j = !j;
		}
	}
	else
		exec_cmd(data->cmds[0], data, 0 , 0);
}