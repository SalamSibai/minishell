/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:57:59 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/30 22:01:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function add the qoutes after the equal sign in the variable 
 * only if the equal sign is present in the variable
 * 
 * @param value 
 * @return char * to the updated value with the qoutes
 */
char	*add_quotes(char *value)
{
	char	*env_value;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	env_value = NULL;
	if (ft_strchr(value, '='))
	{
		if (*ft_strchr(value, '=') + 1 == '\"')
			return (value);
		tmp = ft_strndup(value, (ft_strchr(value, '=') + 1 - value));
		tmp1 = ft_strjoin("\"", ft_strchr(value, '=') + 1);
		tmp2 = ft_strjoin(tmp1, "\"");
		env_value = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp1);
		free(tmp2);
	}
	else
		env_value = ft_strdup(value);
	return (env_value);
}

/**
 * @brief this function will print the env list value on the stdout with the 
 * the extension of "declare -x"
 * @param env the env sturcture to print from the env list 
 */
void	print_env(t_list *env, bool export)
{
	t_list	*tmp;
	char	*quoted_value;

	tmp = env;
	quoted_value = NULL;
	while (env)
	{
		if (export)
		{
			bubble_sort(env, ft_strcmp);
			ft_putstr_fd("declare -x ", 1);
			quoted_value = add_quotes(env->content);
			ft_putendl_fd(quoted_value, 1);
			free(quoted_value);
		}
		else if (ft_strchr(env->content, '='))
			ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	env = tmp;
}

/**
*
* @brief adds new env to env list
* @param value char* the value to add
* @param env t_env sturcture contains the enviroment list to add to it
* @returns int 0 if sucess
*/
int	env_add(char *value, t_list *env)
{
	t_list	*new;
	t_list	*tmp;

	if (env && env->content == NULL)
	{
		env->content = ft_strdup(value);
		return (0);
	}
	new = ft_lstnew(value);
	while (env && env->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

/**
 * @brief this function set the export attribute for variables and 
 * it'll add the variable to the env and itll print it to the stdout 
 * it also check if the variable is already added 
 * @param args an array of string of the variable that wanna be added 
 * to the export list
 * @param env t_env the list that contains all
 *  the enviroment values to add on the new variable
 * @return it return zero on success
 */
bool	ft_export(t_cmd *cmd, t_list *export_env, t_list *env)
{
	t_list	*args;

	if (!cmd->args)
		print_env(export_env, true);
	else
	{
		args = cmd->args;
		while (cmd->args)
		{
			if (!is_valid_env(cmd->args->content) 
				|| ft_strncmp(cmd->args->content, "=", 1) == 0)
				return (print_error(cmd->args->content));
			if (!is_in_env(export_env, cmd->args->content))
				env_add(cmd->args->content, export_env);
			if (!is_in_env(env, cmd->args->content))
				env_add(cmd->args->content, env);
			cmd->args = cmd->args->next;
		}
		cmd->args = args;
	}
	return (true);
}
