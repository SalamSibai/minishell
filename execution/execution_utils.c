/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:00:18 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/20 21:39:37 by ssibai           ###   ########.fr       */
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
	char 	*full_cmd;
	char	*temp;
	temp = ft_strjoin(cmd->cmd_str, " ");
	if (!temp)
		return (false);
	cmd->cmd_with_flag = ft_strjoin(temp, cmd->flag);
	if (!cmd->cmd_with_flag)
		return (false);
	free (temp);
	return (true);
}
