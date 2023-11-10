/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:10:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 17:54:14 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to set the coordinates of an object to a given set.
 * Sets the object's coordinates to zero if the set is NULL;
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_coords *new_coords	-> pointer to the new coordinates' structure
 * @return t_object *			-> pointer to the newly modified object structure
 */
t_object	*set_object_coords(t_object *to_set, t_coords *new_coords)
{
	if (!to_set)
		return (NULL);
	if (new_coords)
		to_set->coords = *new_coords;
	else
		ft_bzero(&to_set->coords, sizeof(t_coords));
	return (to_set);
}

/*
 * Function to change the orientation vector of an object to a given one.
 * Sets the object's vector to zero if the parameter vector is NULL.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_vector *new_vector	-> pointer to the new vector's structure
 * @return t_object *			-> pointer to the newly modified object structure
 */
t_object	*set_object_orientation(t_object *to_set, t_vector *new_vector)
{
	if (!to_set)
		return (NULL);
	if (new_vector)
		to_set->orientation_vector = *new_vector;
	else
		ft_bzero(&to_set->orientation_vector, sizeof(t_vector));
	return (to_set);
}

/*
 * Function to change the color of an object to a given rgb set.
 * Sets the object's color to 0:0:0 if the parameter color is NULL.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_rgb_color *new_color-> pointer to the new color's structure
 * @return t_object *			-> pointer to the newly modified object structure
 */
t_object	*set_object_color(t_object *to_set, t_rgb_color *new_color)
{
	t_rgb_color	*color_to_set;

	if (!to_set || to_set->has_color == false)
		return (NULL);
	if (to_set->type == SPHERE_OBJ)
		color_to_set = &to_set->special_data.sphere.color;
	if (to_set->type == PLANE_OBJ)
		color_to_set = &to_set->special_data.plane.color;
	if (to_set->type == CYLINDER_OBJ)
		color_to_set = &to_set->special_data.cylinder.color;
	if (new_color)
		*color_to_set = *new_color;
	else
		ft_bzero(color_to_set, sizeof(t_rgb_color));
	return (to_set);
}
