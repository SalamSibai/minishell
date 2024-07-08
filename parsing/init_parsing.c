/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:11 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 14:17:11 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_double_quotes(t_var *var, t_token **tkns, char *buff)
{
	int	c;

	c = var->i;
	while (buff[c] && buff[++c] != '\"')
		;
	if (c > var->i)
	{
		var->type = DQOUTES;
		var->expandable = true;
		var->len = (c - var->i - 1);
		var->c = (var->i + 1);
		malloc_qoutes_token(tkns, buff, var);
	}
	var->i = c + 1;
}

void	handle_single_quotes(t_var *var, t_token **tkns, char *buff)
{
	int	c;

	c = var->i;
	while (buff[c] && buff[++c] != '\'')
		;
	if (c > var->i)
	{
		var->type = SQOUTES;
		var->expandable = false;
		var->len = (c - var->i - 1);
		var->c = (var->i + 1);
		malloc_qoutes_token(tkns, buff, var);
	}
	var->i = c + 1;
}

void	handle_other_chars(t_var *var, t_token **tkns, char *buff)
{
	int	c;

	c = var->i;
	while (buff[c] && !ft_isspace(buff[c]) && buff[c] != '|' && buff[c] != '>'
		&& buff[c] != '<' && buff[c] != '\"' && buff[c] != '\'')
		c++;
	if (c > var->i)
	{
		var->len = c - var->i;
		var->x = 0;
		var->c = var->i;
		malloc_each_token(var, tkns, buff);
	}
	var->i = c;
}

void	handle_special_chars(t_var *var, t_token **tkns, char *buff)
{
	int	c;

	c = var->i;
	var->c = c;
	if ((buff[c] == '>' && buff[c + 1] == '>') || (buff[c] == '<'
			&& buff[c + 1] == '<'))
	{
		var->x = 2;
		var->len = 2;
		malloc_each_token(var, tkns, buff);
	}
	else if (buff[c] == '>' && buff[c + 1] != '\0' && buff[c + 1] == '|')
	{
		var->x = 2;
		var->len = 1;
		malloc_each_token(var, tkns, buff);
	}
	else if (buff[c] == '|' || buff[c] == '>' || buff[c] == '<')
	{
		var->x = 1;
		var->len = 1;
		malloc_each_token(var, tkns, buff);
	}
}

void	scan(char *buff, t_token **tkns)
{
	t_var	var;

	var.i = 0;
	var.tkn_ctr = 0;
	while (buff[var.i])
	{
		var.i += ft_skipspaces(buff + var.i);
		if (buff[var.i] == '\"')
			handle_double_quotes(&var, tkns, buff);
		else if (buff[var.i] == '\'')
			handle_single_quotes(&var, tkns, buff);
		else if (buff[var.i] == '|' || buff[var.i] == '>' || buff[var.i] == '<')
			handle_special_chars(&var, tkns, buff);
		else
			handle_other_chars(&var, tkns, buff);
	}
	tkns[var.tkn_ctr] = NULL;
}
