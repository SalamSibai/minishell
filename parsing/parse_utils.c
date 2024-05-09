/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:05 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/08 13:52:56 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

int			ft_panic(char *message, int ret)
{
    //add a function call to cleanup and exit program (if needed)
	return (ft_putendl_fd(message, 2), free(message), ret);
}

void	*ft_safe_malloc(size_t size, char *msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_panic(ft_strjoin("ERROR: MALLOC FAILED IN ", msg), 0), NULL);
 	return (ptr);
}