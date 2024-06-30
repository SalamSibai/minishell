/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:37:29 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/30 10:40:21 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function count all the characters in the double array string
 * @param env char ** a string of arrays that contains the values
 * @return the length of the double array characters
 */
int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/**
 * @brief this function prints out the env on the stdout
 * @param env t_env the list that contains all the enviroment contents
 * @return it returns zero when succses
 */
int	ft_env(t_list *env)
{
	print_env(env, false);
	return (0);
}
