/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:33:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/12 10:28:27 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to retrieve the pointer to the first t_object structure of the given
 * type in an array of objects.
 *
 * @param unsigned short type	-> type of the object to look for
 * @param t_object *objects_list-> array of objects 
 */
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
