/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/10 16:36:41 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/**
 * @brief 
 * 
 */
// void	exec_cmd(t_cmd *cmd, t_data *data)
// {
	
// 	}


/**
 * @brief this function will execute the commands based on the type of command
 * 
 * @param data 
 */
void	execute_cmds(t_data *data)
{
	int		i;

	i = 0;
	// printf("cmds to execute: %s\n", data->cmds[i]->cmd_str);
	while (data->cmds[i] != NULL && data->cmds[i]->cmd_str != NULL)
	{
		if (is_builtin(data->cmds[i]->cmd_str))
			exec_builtin(data->cmds[i], data);
		// else
			// exec_cmd(data->cmds[i], data);
		i++;
	}
	
}