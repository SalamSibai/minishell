/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:31:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/12 20:25:30 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_redirection	*redir_new(int fd, e_token_type type, char *file_name, char *limiter)
{
	t_redirection	*new;

	// new = ft_safe_malloc(sizeof(t_redirection), "REDIRECTION");
	new = ft_calloc(1, sizeof(t_redirection));
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

void	redir_clear(t_redirection **redir)
{
	t_redirection	*tmp;
	t_redirection	*next;

	tmp = *redir;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->file_name)
			free(tmp->file_name);
		if (tmp->limiter)
			free(tmp->limiter);
		free(tmp);
		tmp = next;
	}
	*redir = NULL;
}