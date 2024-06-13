/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:29:32 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 16:42:27 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	if (!haystack && n == 0)
		return (0);
	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (haystack[i] != '\0' && i + needle_len <= n)
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
