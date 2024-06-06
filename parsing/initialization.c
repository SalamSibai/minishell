/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:23:56 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/06 18:34:29 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief function to initialize the redirections structure for each command
 * 
 * @param redir 
 * @param n_redir_in_cmd 
 */
void	init_redirections(t_redirection **redir, int n_redir_in_cmd)
{
	int i;

	i = 0;
	while (i < n_redir_in_cmd - 1)
	{
		redir[i] = ft_safe_malloc(sizeof(t_redirection), "REDIRECTION");
		redir[i]->fd = -1;
		redir[i]->type = NONE;
		redir[i]->file_name = NULL;
		redir[i]->limiter = NULL;
		i++;
	}
	redir[i] = NULL;
}
/**
 * @brief  function to initialize the commands structure 
 * 
 * @param data 
 */
void	init_cmds(t_data *data)
{
	t_cmd		**cmds;
	int			cmd_num;
	int			n_redir;
	int			i;
	int			r_index;

	cmds= data->cmds;
	cmd_num = data->cmd_num;
	i = 0;
	r_index = 0;
	while (i < cmd_num)
	{
		cmds[i] = ft_safe_malloc(sizeof(t_cmd), "CMD");
		cmds[i]->cmd_str = NULL;
		cmds[i]->flag = NULL;
		cmds[i]->args_str = NULL;
		cmds[i]->args = NULL;
		n_redir = count_redir_in_cmd(data->tokens, &r_index);
		if (n_redir > 0)
		{
			cmds[i]->redirection = ft_safe_malloc(sizeof(t_redirection *) * n_redir, "REDIRECTION *"); // dont return ft_panic need to be fix  or put exit in ft_panic
			init_redirections(cmds[i]->redirection, n_redir);
		}
		i++;
	}
}
