/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:31:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/08 13:40:03 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_redirection	*redir_new(int fd, e_token_type type, char *file_name, char *limiter)
{
	t_redirection	*new;

	new = ft_safe_malloc(sizeof(t_redirection), "REDIRECTION");
	new->fd = fd;
	new->type = type;
	new->file_name = file_name;
	new->limiter = limiter;
	new->next = NULL;
	return (new);
}

t_redirection	*redir_last(t_redirection *redir)
{
	if (!redir)
		return (0);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	redir_add_back(t_redirection **redir, t_redirection *new)
{
	t_redirection	*last;

	last = redir_last(*redir);
	if (!last)
		*redir = new;
	else
		last->next = new;
}

void	redir_add_front(t_redirection **redir, t_redirection *new)
{
	new->next = *redir;
	*redir = new;
}

// void	redir_clear(t_redirection **redir)
// {
// 	t_redirection	*tmp;

// 	while (*redir)
// 	{
// 		tmp = (*redir)->next;
// 		free((*redir)->file_name);
// 		free((*redir)->limiter);
// 		free(*redir);
// 		*redir = tmp;
// 	}
// }