/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:21:59 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/13 21:30:06 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Redirecting input includes:

	1) getting heredoc input
	

*/

bool	redirect_input(t_redirection *redir)
{
	redir->fd = open(redir->file_name, O_RDONLY);
	if (redir->fd < 0)
		return (false);
	return (true);
}

bool	redirect_output(t_redirection *redir)
{
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
		return (false);
	return (true);
}

bool	redirect_append(t_redirection *redir)
{
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
		return (false);
	return (true);
}
