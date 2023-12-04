/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:10:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/23 23:03:18 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to set the coordinates of an object to a given set.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_coords new_coords	-> the new coordinates' structure
 * @return t_object *			-> pointer to the newly modified object structure
 */
t_object	*set_object_coords(t_object *to_set, t_coords new_coords)
{
	if (!to_set)
		return (NULL);
	to_set->coords = new_coords;
	return (to_set);
}


/*
 * TODO comment i'm tred
 * TODO add normalise to z
 */
static t_local_axes	*set_local_axes(t_local_axes *to_set, t_vector orientation)
{
	if (!to_set)
		return (NULL);
	get_rotation_matrix(to_set->rotation_matrix, orientation,
		(t_vector){0, 0, 1});
	to_set->x = matrix_vector_rotation((t_vector){1, 0, 0},
		to_set->rotation_matrix);
	to_set->y = matrix_vector_rotation((t_vector){0, 1, 0},
		to_set->rotation_matrix);
	to_set->z = orientation;
	return (to_set);
}

/*
 * Function to change the orientation vector of an object to a given one.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_vector *new_vector	-> the new vector's structure
 * @return t_object *			-> pointer to the newly modified object structure
 */
t_object	*set_object_orientation(t_object *to_set, t_vector new_vector)
{
	if (!to_set)
		return (NULL);
	to_set->orientation_vector = new_vector;
	set_local_axes(&to_set->local_axes, new_vector);
	return (to_set);
}

/*
 * Function to change the color of an object to a given rgb set.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_rgb_color new_color	-> the new color's structure
 * @return t_object *			-> pointer to the newly modified object structure
 */
t_object	*set_object_color(t_object *to_set, t_rgb_color new_color)
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
	*color_to_set = new_color;
	return (to_set);
}
