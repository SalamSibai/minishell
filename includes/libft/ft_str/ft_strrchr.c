/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:29:38 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/13 23:26:43 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
		i++;
	if (c == '\0')
		return (str + i);
	while (--i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
	}
	return (0);
}
