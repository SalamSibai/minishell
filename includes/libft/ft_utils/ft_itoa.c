/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:27:13 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 15:14:13 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_size(long n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long		size;
	long		num;
	char		*nbr;
	const char	*base;

	num = n;
	base = "0123456789";
	size = get_size(num);
	nbr = (char *)malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (0);
	nbr[size] = 0;
	if (n == 0)
		nbr[0] = '0';
	if (n < 0)
	{
		nbr[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		nbr[--size] = base[num % 10];
		num /= 10;
	}
	return (nbr);
}
