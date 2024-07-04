/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:21:59 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/03 22:41:34 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/// @brief executes heredoc and stores input in the redir fd
///			NOTE: HEREDOC APPENDS TO WHATEVER THE OUTPUT IS.
/// @param redir the redir struct
/// @return true if open succeeds.
bool	execute_heredoc(t_cmd *cmd, t_redirection *redir)
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
		if (!(ft_strncmp(line, redir->limiter, in_len)) && line[in_len] == '\n')
			break ;
		write(pipe_in[1], line, ft_strlen(line));
		free(line);
		write (1, "> ", 2);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_in[1]);
	cmd->fd_in = pipe_in[0];
	return (true);
}

bool	get_input(t_cmd *cmd, bool heredoc, t_redirection *redir)
{
	char	 *path;
	char	*file_path1;
	char	*file_path;
	char	cwd[PATH_MAX];

	if (cmd->fd_in != -1)
	{
		if (!close_fd(cmd->fd_in))
			return (false);
	}
	if (!heredoc)
	{
		path = getcwd(cwd, PATH_MAX);
		file_path1 = ft_strjoin(path, "/");
		file_path = ft_strjoin(file_path1, redir->file_name);
		ft_free(&file_path1, 'p');
		if (access(file_path, R_OK) != 0)
		{
			return (free(file_path), false);
		}
		ft_free(&file_path, 'p');
		cmd->fd_in = open(redir->file_name, O_RDONLY);
		if (cmd->fd_in < 0)
		{
			return (false);
		}
	}
	else
	{
		if (!execute_heredoc(cmd, redir))
			return (false);
	}
	return (true);
}
