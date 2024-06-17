/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:27:51 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/18 01:05:56 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief this function count the number of the strings in the array of string give
 * @param args An array of strings representing the command and its arguments.
 * @return the numbers of arguments in the array of strings
 */
int			nb_args(t_list *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
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
int		ft_echo(t_cmd *cmd)
{
	int		nl;
	t_list	*args;
	int		fd;
	
	if (!cmd->redirection)
		fd = 0;
	else
		fd = redir_last(cmd->redirection)->fd;
	args = cmd->args;
	nl = 1;
	if (nb_args(args) > 1)
	{
		if (cmd->flag && ft_strncmp(cmd->flag, "-n", 2) == 0)
			nl = 0;
	}
	while (args)
	{
		//how could we find the last redirection output file to write to it??
		ft_putstr_fd(args->content, fd);
		args = args->next;
		if (args)
			ft_putstr_fd(" ", fd);
	}
	if (nl)
		ft_putstr_fd("\n", fd);
	return (0);
}