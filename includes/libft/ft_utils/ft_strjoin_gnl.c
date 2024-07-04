/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:08:33 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/04 05:53:12 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcat(ft_strcpy(res, (char *)s1), (char *)s2);
		return (free((char *)s1), res);
	}
	else if (s1 != NULL && s2 == NULL)
	{
		return (free((char *)s2), ft_strcpy(res, (char *)s1));
	}
	else if (s1 == NULL && s2 != NULL)
		return (free((char *)s1), ft_strcpy(res, (char *)s2));
	else
		return (free((char *)s1), NULL);
}
