/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:43:15 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/29 20:53:38 by ssibai           ###   ########.fr       */
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
/*
	to validate the entire input:
		1) if only 1 id, must be an executable that works
		2) if heredoc, next token must be an ID
		3) if redirection into a file (>), its fine.
		4) if appending into a file, its fine
		
		 we must have an ID that is not an executable
		5) if redirection from a file, the file we are redirecting from must exist in the directory provided
		6) NO DOUBLE REDIRECTIONS AFTER ONE ANOTHER (except heredoc)
		7) a pipe must have an input its reading from, and an output its reading to
*/

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