/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 05:46:16 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/04 05:46:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
				return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	size_t	args_num;
	int		exit_code;
	t_list	*temp_args;
	size_t	flags_num;
	t_list	*temp_flags;

	temp_args = cmd->args;
	args_num = ft_lstsize(cmd->args);
	flags_num = ft_lstsize(cmd->flag);
	temp_flags = cmd->flag;
	if (args_num == 0 && flags_num == 0)
	{
		cleanup(data);
		exit(0);
	}
	else if (args_num > 2 || flags_num > 1)
		error_handler(TOO_MANY_ARG, IN_REDIR_ER, data, true);
	else if (args_num == 2 &&  flags_num == 0)
	{
			if (ft_strcmp(temp_args->content, "-") == 0)
			{
				temp_args = temp_args->next;
				if (!ft_isnum(temp_args->content))
					error_handler(NUMERIC_REQ_MSG, NUM_REQ_ER, data, true);
				exit_code = 156;
			}
			else if (ft_strcmp(temp_args->content, "+") == 0)
			{
				temp_args = temp_args->next;
				if (!ft_isnum(temp_args->content))
					error_handler(NUMERIC_REQ_MSG, NUM_REQ_ER, data, true);
				exit_code = ft_atoi(temp_args->content);
				if (exit_code > 255)
					exit_code = exit_code % 256;
			}
			else
				error_handler(TOO_MANY_ARG, IN_REDIR_ER, data, true);
	}
	else
	{
		if (flags_num == 1 && args_num == 0)
		{
			if (!ft_isnum(temp_flags->content))
				error_handler(NUMERIC_REQ_MSG, NUM_REQ_ER, data, true);
			exit_code = 156;
		}
		if (flags_num == 0 && args_num == 1)
		{
			if (!ft_isnum(temp_args->content))
				error_handler(NUMERIC_REQ_MSG, NUM_REQ_ER, data, true);
			exit_code = ft_atoi(temp_args->content);
			if (exit_code > 255)
				exit_code = exit_code % 256;
		}
	}
	cleanup(data);
	exit(exit_code);		
}
