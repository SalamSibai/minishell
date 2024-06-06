/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:37:29 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/06 13:57:08 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function count all the characters in the double array string
 * @param env char ** a string of arrays that contains the values
 * @return the length of the double array characters
 */
int			str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
/**
 * @brief this function uses bubble sort to sort the value based on its alphabatic order
 * @param tab char ** a string of arrays that contains the value to sorted based on their alphabatic order
 * @param env_len int to count the number of the total characters in the double array
 */
void		sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}
/**
 * @brief this function initialze the env list and malloc a space in the memory
 * for the list and the value to be added to the list, itll keep adding the values until theres no more to be added
 * also uses bubble sort to sort the values to be used by export 
 * @param mini t_execution * this is the structure for the minishell that contains the env to be added in
 * @param env_array char ** this is a string of array that contains the value to be added in the list 
 * @return it returns -1 if it failed to save memeory for the values and 0 if successfull
 */
int		env_init(t_data *data, char **env_array)
{
	t_list	*env;
	t_list	*new;
	int		i;
	
	// sort_env(env_array, str_env_len(env_array));
	if (!(env = malloc(sizeof(t_list))))
		return (-1);
	env->content = ft_strdup(env_array[0]);
	env->next = NULL;
	data->env = env;
	i = 1;
	while (env_array[i])
	{
		if (!(new = malloc(sizeof(t_list))))
			return (1);
		new->content = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

/**
 * @brief this function prints out the env on the stdout
 * @param env t_env the list that contains all the enviroment contents
 * @return it returns zero when succses
 */
int		ft_env(t_list *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->content, 1);
	return (0);
}
