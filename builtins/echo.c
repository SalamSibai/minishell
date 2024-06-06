/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:27:51 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/06 13:57:32 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief this function count the number of the strings in the array of string give
 * @param args An array of strings representing the command and its arguments.
 * @return the numbers of arguments in the array of strings
 */
int			nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
/**
 * @brief this function display the a line of text that given by args[0]
 * 
 *
 * @param args An array of strings representing the command and its arguments.
 * an array of strings represent the text to be displayed in args[0]
 * and args[i] will be the option of to display the text for example with a new line 
 * @return itll return zero on succes
 */
int		ft_echo(char **args)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 1;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			i++;
			n_option = 1;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[1][0])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (n_option == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}