/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:27:01 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 15:17:28 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mult;

	if (size && (count > (UINT16_MAX / size)))
		return (0);
	mult = count * size;
	ptr = (void *)malloc(sizeof(void) * (mult));
	if (!ptr)
		return (0);
	ft_bzero(ptr, mult);
	return (ptr);
}
