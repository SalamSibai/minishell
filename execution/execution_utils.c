/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:00:18 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/22 15:36:09 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief returns the path where the cmd is
/// @return true if the path was found
bool get_path(t_data *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (data->path[i] != NULL)
	{
		cmd->cmd_path = ft_strjoin(data->path[i], cmd->cmd_str);
		if (access(cmd->cmd_path, F_OK) == 0)
			return (true);
		free(cmd->cmd_path);
		i ++;
	}
	return (false);
}

/// @brief fills the double pointer that holds the cmd and its flags &args
/// @return true if it succeeds.
bool	join_cmd_and_flag(t_cmd *cmd)
{
	t_list	*args_temp;
	int		size;
	int		i;

	i = 1;
	size = ft_lstsize(cmd->args);
	if (cmd->flag)
		size ++;
	cmd->cmd_with_flag = ft_calloc(size + 2, sizeof(char *));
	args_temp = cmd->args;
	cmd->cmd_with_flag[0] = ft_strdup(cmd->cmd_str);
	if (cmd->flag)
		cmd->cmd_with_flag[i++] = ft_strdup(cmd->flag);
	while (args_temp)
	{
		cmd->cmd_with_flag[i] = ft_strdup(args_temp->content);
		args_temp = args_temp->next;
		i ++;
	}
	cmd->cmd_with_flag[i] = NULL;
	if (!cmd->cmd_with_flag)
		return (false);
	return (true);
}
