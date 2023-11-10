/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:33 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:36:37 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (lst[0]->next)
	{
		next = lst[0]->next;
		del(next->content);
		lst[0]->next = next->next;
		free(next);
	}
	del(lst[0]->content);
	free(lst[0]);
	lst[0] = NULL;
}
