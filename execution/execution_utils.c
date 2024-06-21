/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:00:18 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/21 21:46:14 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//create function that checks whether the fd we read/write to is the pipe or the set fd

bool get_path(t_data *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (data->path[i] != NULL)
	{
		cmd->cmd_path = ft_strjoin(data->path[i], cmd->cmd_str);
		if (!cmd->cmd_path)
			return (false);
		if (access(cmd->cmd_path, F_OK) == 0)
			return (true);
		free(cmd->cmd_path);
		i ++;
	}
	return (false);
}

bool	join_cmd_and_flag(t_cmd *cmd)
{
	char	*temp;
	t_list	*args_temp;
	
	args_temp = cmd->args;

	temp = NULL;
	if (cmd->flag)
	{
		temp = ft_strjoin(cmd->cmd_str, " ");
		temp = ft_strjoin(temp, cmd->flag);
	}
	if (cmd->args)
	{
		while (args_temp)
		{
			temp = ft_strjoin(temp, " ");
			if (!temp)
				return (false);
			temp = ft_strjoin(temp, args_temp->content);
			if (!temp)
				return (false);
			args_temp = args_temp->next;
		}
	}
	cmd->cmd_with_flag = ft_strdup(temp);
	printf("cmd_with_flag: %s\n", cmd->cmd_with_flag);
	if (!cmd->cmd_with_flag)
		return (false);
	free (temp);
	return (true);
}
