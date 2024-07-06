/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:29:42 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 16:47:15 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen((char *)s))
		len = 0;
	else if (len > (size_t)ft_strlen((char *)s + start))
		len = (size_t)ft_strlen((char *)s + start);
	substr = (char *)malloc(sizeof(char) *(len + 1));
	if (!substr)
		return (0);
	while (i < len && s[start] != '\0')
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
