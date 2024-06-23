/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:37:54 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/23 14:15:34 by mohammoh         ###   ########.fr       */
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
bool		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (true);
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	if (ft_strcmp(command, "env") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (true);
	if (ft_strcmp(command, "unset") == 0)
		return (true);
	return (false);
}

/**
 * @brief these builtins function to be executed in the main shell and 
 * to exit the child process
 * @param command 
 * @return true if the command is not a builtin
*/
bool	is_env_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return(true);
	if (ft_strcmp(command, "env") == 0)
		return(true);
	if (ft_strcmp(command, "export") == 0)
		return(true);
	if (ft_strcmp(command, "unset") == 0)
		return(true);
	return (false);
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
		ft_export(cmd->args, data->export_env, data->env);
	if (ft_strcmp(cmd->cmd_str, "unset") == 0)
	{
		ft_unset(cmd->args, data->env);
		ft_unset(cmd->args, data->export_env);
	}
	return (result);
}