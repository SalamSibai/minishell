/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/09 22:39:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// void	exec_cmd(t_cmd *cmd, t_data *data)
// {
	
// 	}

void	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_num)
	{
		free(data->cmds[i]->cmd_str);
		if (data->cmds[i]->flag)
			free(data->cmds[i]->flag);
		// free(data->cmds[i]->args_str);
		if (data->cmds[i]->args)
			free(data->cmds[i]->args);
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);

}

/**
 * @brief this function will execute the commands based on the type of command
 * 
 * @param data 
 */
void	execute_cmds(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->cmd_num)
	{
		if (is_builtin(data->cmds[i]->cmd_str))
			exec_builtin(data->cmds[i], data);
		else
			// exec_cmd(data->cmds[i], data);
		ft_free_all(data);
		i++;
	}
	
}