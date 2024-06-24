/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:43:15 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/24 17:57:11 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	validate_syntax(char *line)
{
	if (!validate_unbalanced_qoutes(line))
		return (false);
	if (!validate_pipes(line))
		return (false);
	// if (!validate_redirection(line))
	// 	return (false);
	// if (!validate_append(line))
	// 	return (false);
	return (true);
}

/***********pre-parsing***********/

//check for syntax errors
//check error in double quotes			DONE
//checl error in single quotes			DONE
//check error in pipes
//check error in redirections
//check error in heredoc
//check error in append
//check error in outfile/infile


//command 1 |      command 2 | command 3



//token merge  