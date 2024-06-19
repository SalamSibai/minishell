/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:45:24 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/19 13:27:39 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/**
 * @brief 
 * 
 */
// void	exec_cmd(t_cmd *cmd, t_data *data, int i, int j)
// {
// 	if (is_builtin(cmd->cmd_str))
// 		exec_builtin(cmd, data);
// 	else
// 	{
		
// 	}
// }

/**
 * @brief this function will execute the commands based on the type of command
 * 
 * @param data 
 */
// void	execution(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	// check_redirections(data->cmds);

// 	/*
// 	check number of comands
// 		if 1: execute that comand and print into the redirected fd if available

// 		if its the last command:
// 			redirect to whatever the last output redirection is (if available)
// 			otherwise print on std out
			
// 		else:
// 			redirect to the pipe (write end) ONLY IF THERES NO REDIRECTION OUTPUT
		
// 		when reading:

// 		if its the first command:
// 			read from either the file, the heredoc (redir->fd), or stdin (ONLY IF PASSES)
// 		else
// 			read from the read end of the previous pipe 
// 	*/

// 	// if (data->cmd_num > 1)
// 	// {
// 	// 	while (data->cmds[i] != NULL && data->cmds[i]->cmd_str != NULL)
// 	// 	{
// 	// 		exec_cmd(data->cmds[i], data, i, j);
// 	// 		i++;
// 	// 		j = !j;
// 	// 	}
// 	// }
// 	// else
// 	// //	exec_cmd(data->cmds[0], data, 0 , 0);
// }