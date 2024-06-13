/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:21:59 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/13 19:39:03 by ssibai           ###   ########.fr       */
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
