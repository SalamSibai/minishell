/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:17:41 by ssibai            #+#    #+#             */
/*   Updated: 2024/06/30 16:53:58 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief where error msgs are printed, and data is redirected to the necessary
 *        functions depending on what is needed to be freed.. etc
 * @param err_str the error msg (that have been defined in the header)
 * @param err_type the type of the error (to check what should be freed, also defined in the header)
 * @param data reference to data
 * @param done whether minishell program should be terminated or not
 */
void error_handler(char *err_str, int err_type, t_data *data, bool done)
{
    perror(err_str);
    if (err_type == INVALID_IN_ER)
    {
        g_exit_status = 258;
        free(data->buf);
    }
    else if (err_type == IN_REDIR_ER || err_type == OUT_REDIR_ER)
    {
        g_exit_status = 1;
        //free(data->buf);
    }
    else if (err_type == PATH_ER)
    {
        g_exit_status = 127;
    }
    else if (err_type == PIPE_ER)
    {
        g_exit_status = 141;
    }
    else if (err_type == FORK_ER)
    {
        g_exit_status = 11;
    }
    else if (err_type == CMD_ER)
    {
        g_exit_status = 2;
    }
	if (done)
	{
		cleanup(data);
		exit(g_exit_status);
	}
}