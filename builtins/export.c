/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ++4 <++4@students.42abudhabi.ae>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:57:59 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/07 23:51:34 by ++4              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief this function will print the env list value on the stdout with the 
 * the extension of "declare -x"
 * @param env the env sturcture to print from the env list 
 */
void		print_env(t_list *env)
{
	while (env->next && env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
}
/**
*
* @brief adds new env to env list
* @param value char* the value to add
* @param env t_env sturcture contains the enviroment list to add to it
* @returns int 0 if sucess
*/
int			env_add(char *value, t_list *env)
{
	t_list	*new;
	t_list	*tmp;

	if (env && env->content == NULL)
	{
		// env->content = ft_strdup("\"");
		env->content = ft_strdup(value);
		// env->content = ft_strdup(value);
		// env->content = ft_strjoin(env->content, "\"");
		return (0);
	}
	if (!(new = malloc(sizeof(t_list))))
		return (-1);
	new->content = ft_strdup(value);
	while (env && env->next && env->next->next)
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
 * @param args an array of string of the variable that wanna be added to the export list
 * @param env t_env the list that contains all the enviroment values to add on the new variable
 * @return it return zero on success
 */
int			ft_export(t_list *args, t_list *env)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	if (!args)
	{
		// printf("export: not enough arguments\n");
		print_env(env);
		return (1);
	}
	else
	{
		error_ret = is_valid_env(args->content);
		if (ft_strncmp(args->content, "=", 1) == 0)
			error_ret = -42;
		if (error_ret <= 0)
			return (print_error(error_ret, args->content));
		new_env = is_in_env(env, args->content);
		if (new_env == 0)
			env_add(args->content, env);
	}
	return (0);
}
