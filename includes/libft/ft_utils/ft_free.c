/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:57:25 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/07 04:48:32 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	free_ptr(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

static void	free_arr(void ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}

void	ft_free(void *address, char target)
{
	if (!address || !target)
		return ;
	if (target == 'p')
		free_ptr((void **)address);
	else if (target == 'a')
		free_arr((void ***)address);
	else
		return ;
}

/*
	static void	free_ptr(void **ptr)
	{
		if (!ptr || !(*ptr))
			we are checking if the ptr it self is NULL
        	or the value it points to is NULL, \0
	}

	arr: Pointer to a pointer to a pointer to void (e.g., void ***).
	*arr: Dereferencing once gives you a
		pointer to a pointer to void (e.g., void **).
	cpy: Assigned the dereferenced value of *arr,
		so cpy is also a pointer to a pointer to void (e.g., void **).

	if we used the *arr directly instead of cpy,
	at the time we free(*arr) we will be freeing the NULL.
*/