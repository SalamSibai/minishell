/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:58:41 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/22 21:22:37 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * still needs updates to work with our new structure 
 * @brief remove the variable if found in the env list
 * @param env  t_env sturcture contains the enviroment list
 * @param args the string that need to be compared with the enviroment value thats in the enviroment list to be removed
 * @return returns 1 if founded the enviroment that need to be removed
 */
int			is_in_env_remove(t_list *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];
	t_list	*head;

	head = env;
	get_env_name(var_name, args);
	while (env)
	{
		if ((env)->next && (env)->next->content)
		{
			get_env_name(env_name, (env)->next->content);
			if (ft_strcmp(var_name, env_name) == 0)
				env->next = env->next->next;
		}
		env = env->next;
	}
	env = head;
	return (0);
}
/**
 *  need to update to make it work with our new structure /////////
 * @brief this function unset the values and attributes of the variable 
 * in the export list and the enviroment list
 * @param args its an array of strings the contains the strings in the command
 * @param env t_env sturcture contains the enviroment list
 * @return it returns 0 if theres no arguments for unset and it return on succes 
 */
int	ft_unset(t_list *args, t_list *env)
{
	t_list *tmp;

	tmp = args;
	if (!tmp)
		return (0);
	while (tmp)
	{
		is_in_env_remove(env, tmp->content);
		tmp = tmp->next;
	}
	return (1);
}
