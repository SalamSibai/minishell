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

/// @brief executes heredoc and stores input in the redir fd
///			NOTE: HEREDOC APPENDS TO WHATEVER THE OUTPUT IS.
/// @param redir the redir struct
/// @return true if open succeeds.
bool	execute_heredoc(t_cmd *cmd, t_redirection *redir, t_list *env, t_data *data)
{
	int		in_len;
	char	*line;
	char	*expanded_line;
	int		pipe_in[2];

	if (pipe(pipe_in) == -1)
		return (false);
	in_len = ft_strlen(redir->limiter);
	write (1, "> ", 2);
	line = get_next_line(0);
	while (line)
	{
		if (!(ft_strncmp(line, redir->limiter, in_len)) && line[in_len + 1] == '\0')
			break ;
		if (strchr(line, '$'))
		{
			expanded_line = replace_env_var(line, env, data);
			free(line);
			line = expanded_line;
		}
		write(pipe_in[1], line, ft_strlen(line));
		write (1, "> ", 2);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_in[1]);
	cmd->fd_in = pipe_in[0];
	return (true);
}

bool	get_input(t_cmd *cmd, bool heredoc, t_redirection *redir, t_data *data)
{
	char	*file_path;
	t_list	*env;

	env = data->env;
	if (cmd->fd_in != -1)
	{
		if (!close_fd(cmd->fd_in))
			return (false);
	}
	if (!heredoc)
	{	
		file_path = get_file_path(redir->file_name);
		// if (!file_path)

		if (access(file_path, R_OK) != 0)
		{
			//set error code to access denied?
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
		if (!execute_heredoc(cmd, redir, env, data))
			return (false);
	}
	return (true);
}
