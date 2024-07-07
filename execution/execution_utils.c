/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:00:18 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/07 01:25:59 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


bool	is_directory(const char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		if (access(path, X_OK) != 0)
			return (false);
		return (true);
	}
	return (false);
}

/// @brief returns the path where the cmd is
/// @return true if the path was found
bool get_path(t_data *data, t_cmd *cmd, bool *cmd_exists)
{
	int		i;

	i = 0;
	if (access(cmd->cmd_str, X_OK) == 0)
	{
		cmd->cmd_path = ft_strdup(cmd->cmd_str);
		return (true);
	}
	if (data->path[i] == NULL)
		return (false);
	while (data->path[i] != NULL)
	{
		cmd->cmd_path = ft_strjoin(data->path[i], cmd->cmd_str);
		if (access(cmd->cmd_path, F_OK) == 0)
			return (true);
		free(cmd->cmd_path);
		i ++;
	}
	*cmd_exists = false;
	return (true);
}

/// @brief fills the double pointer that holds the cmd and its flags &args
/// @return true if it succeeds.
bool	join_cmd_and_flag(t_cmd *cmd)
{
	t_list	*args_temp;
	t_list	*flag_temp;
	int		size;
	int		i;

	i = 1;
	size = ft_lstsize(cmd->args);
	if (cmd->flag)
		size ++;
	cmd->cmd_with_flag = ft_calloc(size + 2, sizeof(char *));
	args_temp = cmd->args;
	cmd->cmd_with_flag[0] = ft_strdup(cmd->cmd_str);
	flag_temp = cmd->flag;
	if (cmd->flag)
	{
		cmd->cmd_with_flag[i++] = ft_strdup(cmd->flag->content);
		cmd->flag = cmd->flag->next;
	}
	cmd->flag = flag_temp;
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
