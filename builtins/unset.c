/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:58:41 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/06 13:57:27 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief remove the variable if found in the env list
 * @param env  t_env sturcture contains the enviroment list
 * @param args the string that need to be compared with the enviroment value thats in the enviroment list to be removed
 * @return returns 1 if founded the enviroment that need to be removed
 */
int			is_in_env_remove(t_list *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->content);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			// free(env->value);
			if (env->next->next)
				env->next = env->next->next;
			else
				env->next = NULL;
			return (1);
		}
		env = env->next;
	}
	return (0);
}
/**
 * @brief this function unset the values and attributes of the variable 
 * in the export list and the enviroment list
 * @param args its an array of strings the contains the strings in the command
 * @param env t_env sturcture contains the enviroment list
 * @return it returns 0 if theres no arguments for unset and it return on succes 
 */
int	ft_unset(char **args, t_list *env)
{
	int		i;

	i = 1;
	if (!args[1])
		return (0);
	while (args[i])
		is_in_env_remove(env, args[i++]);
	return (1);
}