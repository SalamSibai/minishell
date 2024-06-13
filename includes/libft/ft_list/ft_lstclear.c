/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:27:30 by mohammoh          #+#    #+#             */
/*   Updated: 2023/07/06 15:27:32 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	next = NULL;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}


// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	if (!lst || !del || !(*lst))
// 		return ;
// 	ft_lstclear(&(*lst)->next, del);
// 	(del)((*lst)->content);
// 	free(*lst);
// 	*lst = NULL;
// }