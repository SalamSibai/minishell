/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:51:26 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/06 18:05:28 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		print_error(int error, const char *arg)
{
	int		i;

	if (error <= 0)
		ft_putstr_fd("export: not a valid identifier: ", 2);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -42))
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (0);
}
/**
 * @brief this function will copy the name of the vairable without its value and the equal sign from the list to be compared with the 
 * the vairable that going be added by export funtion 
 * @param dest
 * @param src 
 * @return itll return the copied characters from the src without the = sign
 */
char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * @brief check if the args that wanna be added to the enviroment
 *  is already in the env list
 * itll loop through the list and itll will compare the variable with the env
 * @param env t_env sturcture contains the enviroment list that itll look through
 * @param args the value of the env that need to be check if it already exist in the list
 * @return it returns 1 on succes of finding the name in the list and 0 on nothing to be found
 */
int			is_in_env(t_list *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->content);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			free(env->content);
			env->content = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
/**
 * @brief this function checks if the env variable is valid or not 
 * in case if the value is digit the env is not valid and if its alpha numeric is also not valid
 * 
 * @param var 
 * @return 
 */
int		is_valid_env(const char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) == 1)
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0)
			return (-1);
		i++;
	}
	if (var[i] != '=')
		return (2);
	return (1);
}