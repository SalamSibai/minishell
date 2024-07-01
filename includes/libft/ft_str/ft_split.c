/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:28:47 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 16:30:41 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	array_length(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		while (str[i] != '\0' && str[i] != c)
			i++;
		count++;
		while (str[i] != '\0' && str[i] == c)
			i++;
	}
	return (count);
}

static char	*wordbyword(char const *str, char c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (0);
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**array;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (array_length(s, c) + 1));
	if (!array)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			array[j] = wordbyword(s + i, c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	array[j] = 0;
	return (array);
}
