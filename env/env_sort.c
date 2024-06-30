/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:07:21 by mohammoh          #+#    #+#             */
/*   Updated: 2024/06/30 14:18:39 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	swap_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

/**
 * @brief this function sorts the linked list using bubble sort
 * 
 * @param head 
 * @param cmp 
 */
void	bubble_sort(t_list *head, int (*cmp)(const char *, const char *))
{
	t_list	*ptr;
	t_list	*last_ptr;
	int		swapped;

	last_ptr = NULL;
	if (!head)
		return ;
	while (1)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next != last_ptr)
		{
			if (cmp(ptr->content, ptr->next->content) > 0)
			{
				swap_content(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last_ptr = ptr;
		if (!swapped)
			break ;
	}
}
