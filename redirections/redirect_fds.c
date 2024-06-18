/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:06 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/18 20:45:22 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	read_infile(t_data *d)
// {
// 	if (dup2(d->infile, STDIN_FILENO) == -1)
// 		return (0);
// 	return (1);
// }

// int	read_pipe(t_pipe *p, int i)
// {
// 	if (dup2(p->fd[i][0], STDIN_FILENO) == -1)
// 		return (0);
// 	return (1);
// }

// int	write_pipe(t_pipe *p, int i)
// {
// 	if (dup2(p->fd[i][1], STDOUT_FILENO) == -1)
// 		return (0);
// 	return (1);
// }

// int	write_outfile(t_data *d)
// {
// 	if (dup2(d->outfile, STDOUT_FILENO) == -1)
// 		return (0);
// 	return (1);
// }

void	redirect_files(t_cmd *cmd, int j)
{
	if (i == 0)
	{
		if (read_infile(d) == 0)
			error_handler("Infile: READ dupe error\n", 1, d, p);
	}
	else
	{
		if (read_pipe(p, !j) == 0)
			error_handler("Pipe: READ dupe error\n", 1, d, p);
	}
	if (i == d->cmd_num -1)
	{
		if (write_outfile(d) == 0)
			error_handler("Outfile: WRITE dupe error\n", 1, d, p);
	}
	else
	{
		if (write_pipe(p, j) == 0)
			error_handler("Pipe: WRITE dupe error\n", 1, d, p);
	}
}
