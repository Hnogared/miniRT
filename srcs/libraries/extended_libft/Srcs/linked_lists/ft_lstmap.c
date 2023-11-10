/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:32 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:37:23 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	start = ft_lstnew(f(lst->content));
	current = start;
	while (lst->next)
	{
		lst = lst->next;
		current->next = ft_lstnew(f(lst->content));
		if (!current->next)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		current = current->next;
	}
	return (start);
}
