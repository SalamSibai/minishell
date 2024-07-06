/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:26:59 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/13 23:26:43 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*is_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return ((char *)str + i);
}

static int	check_if_negative(int sign, char c)
{
	if (c == '-')
		sign = -sign;
	return (sign);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	long			ret;

	i = 0;
	ret = 0;
	sign = 1;
	str = is_space(str);
	while ((str[i] == '+' || str[i] == '-')
		&& (str[i + 1] != '+' && str[i + 1] != '-'))
	{
		sign = check_if_negative(sign, str[i]);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if ((sign == -1 && (ret * 10 < ret)))
			return (0);
		if (sign == 1 && (ret * 10 < ret))
			return (-1);
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (sign * ret);
}
