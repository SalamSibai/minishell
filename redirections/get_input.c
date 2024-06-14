/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:21:59 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/14 20:55:35 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief executes heredoc and stores input in the redir fd
///			NOTE: HEREDOC APPENDS TO WHATEVER THE OUTPUT IS.
/// @param redir the redir struct
/// @return true if open succeeds.
bool	execute_heredoc(t_redirection *redir)
{
	int		in_len;
	char	*line;
	int		pipe_in[2];

	if (pipe(pipe_in) == -1)
		return (false);
	in_len = ft_strlen(redir->limiter);
	write (1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (!(ft_strncmp(line, redir->file_name, in_len)) && line[in_len + 1] == '\0')
			break ;
		write(pipe_in[1], line, ft_strlen(line));
		write (1, "> ", 2);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_in[1]);
	redir->fd = pipe_in[0];
	return (true);
}

bool	get_input(t_redirection *redir, bool heredoc)
{
	if (!heredoc)
	{
		redir->fd = open(redir->file_name, O_RDONLY);
		if (redir->fd < 0)
			return (false);
	}
	else
	{
		if (!execute_heredoc(redir))
			return (false);
	}
	return (true);
}
