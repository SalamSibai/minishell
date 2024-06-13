/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:28:22 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/03 14:28:22 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	index;
	char	*dest;
	char	*source;

	index = 0;
	dest = (char *)dst;
	source = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dest <= source || dest >= (source + n))
	{
		ft_memcpy(dst, src, n);
	}
	else
	{
		index = n - 1;
		while (n--)
		{
			dest[index] = source[index];
			index--;
		}
	}
	return (dst);
}
