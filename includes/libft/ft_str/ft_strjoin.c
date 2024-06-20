/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:22:56 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 16:34:31 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//checks leaks 
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	size = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcat(ft_strcpy(res, (char *)s1), (char *)s2);
		return (res);
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



// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;

// 	str = (char*)malloc(
// 		sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 	{
// 		str[j++] = s1[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (s2[i])
// 	{
// 		str[j++] = s2[i];
// 		i++;
// 	}
// 	str[j] = 0;
// 	return (str);
// }