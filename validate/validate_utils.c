/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:47:04 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:23 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_peek(char **ps, char *es, char *token)
{
	char	*s;

	s = *ps;
	while (s < es && ft_isspace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(token, *s));
}

bool	validate_unbalanced_qoutes(char *line)
{
	int		i;
	char	qoute;
 
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			qoute = line[i];
			i++;
			while (line[i] && line[i] != qoute)
				i++;
			if (!line[i])
			{
				printf("Error: unmatched qoutes\n"); 
				return (false);
			}
			i++;
		}
		else
			i++;
	}
	return (true);
}

bool validate_pipes(char *line)
{
	char *ps;
	char *es;

	ps = line;
	es = line + ft_strlen(line);
	while (ps < es && ft_isspace(*ps))
		ps++;
	if (ft_peek(&ps, es, "|"))
	{
		printf("Error: syntax error near unexpected token 1`|'\n");
		return (false);
	}
	while (ps < es)
	{
		if (*ps == '|')
		{
			ps++;
			while (ps < es && ft_isspace(*ps))
				ps++;
			if (ps == es || *ps == '|')
			{
				printf("Error: syntax error near unexpected token 2`|'\n");
				return (false);
			}
		}
		else
			ps++;
	}
	return true;
}



// int main()
// {
// 	char *line = strdup(" r >'ls > >|  cat ' | wc" );
// 	validate_syntax(line);
// 	return 0;
// }
