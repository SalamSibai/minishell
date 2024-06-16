/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:41:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/14 20:57:11 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	set_output(t_redirection *redir, bool append)
{
	if (!append)
	{
		redir->fd = open(redir->file_name,
				O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (!redir->fd)
			return (false);
	}
	else
	{
		redir->fd =  open(redir->file_name,
				O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (!redir->fd)
			return (false);
	}
	return (true);
}
