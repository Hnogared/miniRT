/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:33:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/07 16:13:33 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*get_object_ptr(unsigned short type, t_object *objects_list,
	int list_size)
{
	int	i;

	if (!objects_list)
		return (NULL);
	i = 0;
	while (i < list_size && objects_list[i].type != type)
		i++;
	return ((t_object *)((uintptr_t) &(objects_list[i]) * (i != list_size)));
}
