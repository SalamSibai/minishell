/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/20 21:04:26 by ssibai           ###   ########.fr       */
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
	/*
		WE MUST FORK FIRST AND IN THE CHILD WE REDIRECT AND EXECUTE
	*/
	
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