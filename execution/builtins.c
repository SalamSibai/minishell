/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:37:54 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/18 20:29:55 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief 
 * 
 *
 * @param command 
 * @return 
 */
int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

/**
 * @brief 
 * @param cmd 
 * @param exec 
 * @return 
 */
int		exec_builtin(t_cmd *cmd, t_data *data)
{
	int		result;

	result = 0;
	if (ft_strcmp(cmd->cmd_str, "echo") == 0)
		result = ft_echo(cmd);
	if (ft_strcmp(cmd->cmd_str, "cd") == 0)
		result = ft_cd(cmd, data->env);
	if (ft_strcmp(cmd->cmd_str, "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(cmd->cmd_str, "env") == 0)
		ft_env(data->env);
	if (ft_strcmp(cmd->cmd_str, "export") == 0)
		ft_export(cmd->args, data->env);
	if (ft_strcmp(cmd->cmd_str, "unset") == 0)
		ft_unset(cmd->args, data->env);
	return (result);
}