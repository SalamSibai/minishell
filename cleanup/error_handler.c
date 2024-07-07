/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:17:41 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/07 05:24:28 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief where error msgs are printed, and data is redirected to the necessary
 *        functions depending on what is needed to be freed.. etc
 * @param err_str the error msg (that have been defined in the header)
 * @param err_type the type of the error (to check what should be freed,
 *  also defined in the header)
 * @param data reference to data
 * @param done whether minishell program should be terminated or not
 */

void	done_done(t_data *data, bool done, int exit_code)
{
	if (done)
	{
		if (data)
			cleanup(data);
		exit(exit_code);
	}
}

void	error_handler(char *err_str, int err_type, t_data *data, bool done)
{
	int	exit_code;

	exit_code = 0;
	if (err_str != NULL)
		ft_putstr_fd(err_str, 2);
	if (err_type < 0)
		data->g_exit_status = 0;
	else if (err_type == INVALID_IN_ER)
		data->g_exit_status = 258;
	else if (err_type == IN_REDIR_ER || err_type == OUT_REDIR_ER)
		data->g_exit_status = 1;
	else if (err_type == NUM_REQ_ER)
		data->g_exit_status = 255;
	else if (err_type == PATH_ER)
		data->g_exit_status = 1;
	else if (err_type == DIR_EXEC_ER)
		data->g_exit_status = 126;
	else if (err_type == PIPE_ER)
		data->g_exit_status = 141;
	else if (err_type == FORK_ER)
		data->g_exit_status = 11;
	else if (err_type == CMD_ER)
		data->g_exit_status = 127;
	exit_code = data->g_exit_status;
	done_done(data, done, exit_code);
}
