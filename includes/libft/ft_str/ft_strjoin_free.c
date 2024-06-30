/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:23:15 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/30 22:35:55 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int free_mode)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	ft_strcpy(joined_str, s1);
	ft_strcat(joined_str, s2);
	if (free_mode == 1 || free_mode == 3)
		free(s1);
	if (free_mode == 2 || free_mode == 3)
		free(s2);
	return (joined_str);
}
