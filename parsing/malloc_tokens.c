/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:19:16 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/06 16:30:20 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief this function malloc for each token and set the type of the token 
 * and increments the ctr of the token
 * 
 * @param data 
 */
void	malloc_each_token(int *token_ctr, t_token **tokens, char *buff, 
			int c, size_t len, int *i, int x)
{
	tokens[*token_ctr] = ft_calloc(1, sizeof(t_token));
	tokens[*token_ctr]->token_string = ft_substr(buff, c, len);
	set_type(tokens[*token_ctr]);
	(*token_ctr)++;
	*i += x;
}
/**
 * @brief this function malloc for each token and set the type of the token
 * 
 */
void	malloc_qoutes_token(t_token **tokens, int *token_ctr, char *buff, 
			int c, int len, int type, bool expandable)
{
	tokens[*token_ctr] = ft_calloc(1, sizeof(t_token));
	tokens[*token_ctr]->token_string = ft_substr(buff, c, len);
	tokens[*token_ctr]->type = type;
	tokens[*token_ctr]->expandable = expandable;
	(*token_ctr)++;
}