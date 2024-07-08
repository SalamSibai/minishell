/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:21:59 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/05 07:34:29 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_heredoc(t_data *data, char *line, char *expanded_line, int p[2])
{
	if (strchr(line, '$'))
	{
		expanded_line = replace_env_var(line, data->env, data);
		free(line);
		line = expanded_line;
		write(p[1], line, ft_strlen(line));
		write (1, "> ", 2);
	}
	else
	{
		write(p[1], line, ft_strlen(line));
		write (1, "> ", 2);
		free(line);
	}
}

/// @brief executes heredoc and stores input in the redir fd
///			NOTE: HEREDOC APPENDS TO WHATEVER THE OUTPUT IS.
/// @param redir the redir struct
/// @return true if open succeeds.
bool	execute_heredoc(t_cmd *cmd, t_redirection *redir, t_data *data)
{
	int		in_len;
	char	*line;
	char	*expanded_line;
	int		pipe_in[2];

	expanded_line = NULL;
	if (pipe(pipe_in) == -1)
		return (false);
	in_len = ft_strlen(redir->limiter);
	write (1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (!(ft_strncmp(line, redir->limiter, in_len))
			&& line[in_len + 1] == '\0')
			break ;
		expand_heredoc(data, line, expanded_line, pipe_in);
		line = get_next_line(0);
	}
	close(pipe_in[1]);
	cmd->fd_in = pipe_in[0];
	return (true);
}

bool	get_input(t_cmd *cmd, bool heredoc, t_redirection *redir, t_data *data)
{
	char	*file_path;

	if (cmd->fd_in != -1)
	{
		if (!close_fd(cmd->fd_in))
			return (false);
	}
	if (!heredoc)
	{
		file_path = get_file_path(redir->file_name);
		if (access(file_path, R_OK) != 0)
		{
			return (free(file_path), false);
		}
		ft_free(&file_path, 'p');
		cmd->fd_in = open(redir->file_name, O_RDONLY);
		if (cmd->fd_in < 0)
			return (false);
	}
	else
	{
		if (!execute_heredoc(cmd, redir, data))
			return (false);
	}
	return (true);
}
