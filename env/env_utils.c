/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:51:26 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/22 21:19:37 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool		print_error(const char *arg)
{
	int	i;

	i = 0;
	ft_putstr_fd("export: not a valid identifier: ", 2);
	while (arg[i] && arg[i] != '=')
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (false);
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

	if (!src)
		return (NULL);
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
 *  is already in the env list then change it value to the new added value
 * itll loop through the list and itll will compare the variable with the env
 * @param env t_env sturcture contains the enviroment list that itll look through
 * @param args the value of the env that need to be check if it already exist in the list
 * @return it returns 1 on succes of finding the name in the list and 0 on nothing to be found
 */
bool		is_in_env(t_list *env, char *args)
{
	char	*env_name;
	char	*args_w;
	char	*tmp;
	t_list	*head;


	head = NULL;
	env_name = malloc(BUFF_SIZE);
	memset(env_name, 0, BUFF_SIZE);
	args_w = malloc(BUFF_SIZE);
	memset(args_w, 0, BUFF_SIZE);
	tmp = NULL;
	if (!env_name)
		return false;
	head = env;
	while (env)
	{
		tmp = env->content;
		get_env_name(env_name, tmp);
		get_env_name(args_w, args);
		if (ft_strcmp(env_name, args_w) == 0)
		{
			env->content = ft_strdup(args);
			free(env_name);
			free(args_w);
			args_w = NULL;
			env_name = NULL;
			env = head;
			return (true);
		}
		env = env->next;
	}
	env = head;
	return false;
}
/**
 * @brief this function checks if the env variable is valid or not 
 * in case if the value is digit the env is not valid and if its alpha numeric is also not valid
 * 
 * @param var 
 * @return 
 */
bool	is_valid_env(const char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) == 1)
		return (false);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}