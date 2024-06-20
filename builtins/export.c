/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:57:59 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:00 by mohammoh         ###   ########.fr       */
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
	char *env_value = NULL;
	char *tmp = NULL;
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	
	if (ft_strchr(value, '='))
	{
		if (*ft_strchr(value, '=') + 1 == '\"')
			return (value);
		tmp = ft_strndup(value, (ft_strchr(value, '=') + 1 - value));
		tmp1 = ft_strjoin("\"", ft_strchr(value, '=')+ 1);
		tmp2 = ft_strjoin(tmp1, "\"");
		env_value = ft_strjoin(tmp, tmp2);
	}
	free(tmp);
	free(tmp1);
	free(tmp2);
	return (env_value);
}

/**
 * @brief this function will print the env list value on the stdout with the 
 * the extension of "declare -x"
 * @param env the env sturcture to print from the env list 
 */

// i need to send the t_cmd to give it the fd
void		print_env(t_list *env, bool export)
{
	while (env->next && env)
	{
		if (export)
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
int			env_add(char *value, t_list *env, bool export)
{
	t_list	*new;
	t_list	*tmp;

	if (env && env->content == NULL)
	{
		if (export)
			env->content = ft_strdup(value);
		else
			env->content = add_quotes(value);
		return (0);
	}
	if (export)
		new = ft_lstnew(add_quotes(value));
	else
		new = ft_lstnew(ft_strdup(value));
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
bool		ft_export(t_list *args, t_list *export_env, t_list *env)
{
	if (!args)
		print_env(export_env, true);
	else
	{
		while (args)
		{
			if (!is_valid_env(args->content) || ft_strncmp(args->content, "=", 1) == 0)
				return (print_error(args->content));
			is_in_env(export_env, args->content);
			env_add(args->content, export_env, true);
			env_add(args->content, env, false);
			args = args->next;
		}
	}
	return (true);
}
