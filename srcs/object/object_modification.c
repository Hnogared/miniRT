/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:10:00 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 12:26:25 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to set the coordinates of an object to a given set.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_coords new_coords	-> the new coordinates' structure
 * @[rednudant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*set_object_coords(t_object *to_set, t_coords new_coords)
{
	if (!to_set)
		return (NULL);
	to_set->coords = new_coords;
	return (to_set);
}

/*
 * Function to change the orientation vector, and therefore the local basis, of
 * an object.
 * A camera's orientation vector is the x axis of its local basis while the
 * other objects use their local basis' z axis.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_vector *new_vector	-> the new vector's structure
 * @[redundant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*set_object_orientation(t_object *to_set, t_vector new_vector)
{
	if (!to_set)
		return (NULL);
	if (!new_vector.x && !new_vector.y && !new_vector.z)
		new_vector = (t_vector){1, 0, 0};
	to_set->orientation_vector = normalise(new_vector);
	if (to_set->type == CAMERA_OBJ)
		to_set->local_basis = get_ortho_basis_from_x(new_vector);
	else
		to_set->local_basis = get_ortho_basis_from_z(new_vector);
	return (to_set);
}

/*
 * Function to rotate an object around an axis at a given angle.
 * A camera's orientation vector is the x axis of its local basis while the
 * other objects use their local basis' z axis.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_rotate	-> pointer to the object to rotate
 * @param float angle			-> angle of the rotation to apply
 * @param t_vector axis			-> axis along which to rotate the object
 * @[redundant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*rotate_object(t_object *to_rotate, float angle, t_vector axis)
{
	if (!to_rotate)
		return (NULL);
	to_rotate->local_basis = axial_basis_rotation(to_rotate->local_basis, angle,
			axis);
	if (to_rotate->type == CAMERA_OBJ)
		to_rotate->orientation_vector = to_rotate->local_basis.x;
	else
		to_rotate->orientation_vector = to_rotate->local_basis.z;
	return (to_rotate);
}

/*
 * Function to change the color of an object to a given rgb set.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_rgb_color new_color	-> the new color's structure
 * @[redundant]return t_object *-> pointer to the newly modified object structure
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
	if (to_set->type == LIGHT_OBJ)
		color_to_set = &to_set->special_data.light.color;
	*color_to_set = new_color;
	return (to_set);
}
