/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:19:16 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/08 14:21:16 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function malloc for each token and set the type of the token 
 * and increments the ctr of the token
 * 
 * @param data 
 */
void	malloc_each_token(t_var *var, t_token **tokens, char *buff)
{
	tokens[var->tkn_ctr] = ft_calloc(1, sizeof(t_token));
	tokens[var->tkn_ctr]->token_string = ft_substr(buff, var->c, var->len);
	set_type(tokens[var->tkn_ctr]);
	(var->tkn_ctr)++;
	var->i += var->x;
}

/**
 * @brief this function malloc for each token and set the type of the token
 * 
 */
void	malloc_qoutes_token(t_token **tokens, char *buff, t_var *var)
{
	tokens[var->tkn_ctr] = ft_calloc(1, sizeof(t_token));
	tokens[var->tkn_ctr]->token_string = ft_substr(buff, var->c, var->len);
	tokens[var->tkn_ctr]->type = var->type;
	tokens[var->tkn_ctr]->expandable = var->expandable;
	(var->tkn_ctr)++;
}
