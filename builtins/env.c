/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:37:29 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/19 13:09:41 by mohammoh         ###   ########.fr       */
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
 * @brief this function prints out the env on the stdout
 * @param env t_env the list that contains all the enviroment contents
 * @return it returns zero when succses
 */
int		ft_env(t_list *env)
{
	print_env(env, false);
	return (0);
}
