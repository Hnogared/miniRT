/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:10:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/13 19:56:35 by hnogared         ###   ########.fr       */
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
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the x axis.
 *
 * @param t_vector xxx_orientation	-> the new basis' x axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
static t_basis	get_ortho_basis_from_x(t_vector xxx_orientation)
{
	t_vector	z_axis;
	t_basis		new;

	new.x = normalise(xxx_orientation);
	z_axis = (t_vector){0, 0, 1};
	if (xxx_orientation.x == 0.0f && xxx_orientation.y == 0.0f
		&& xxx_orientation.z == 1.0f)
		new.z = (t_vector){0, -1, 0};
	else if (xxx_orientation.x == 0.0f && xxx_orientation.y == 0.0f
		&& xxx_orientation.z == -1.0f)
		new.z = (t_vector){0, 1, 0};
	else
	{
		new.z = prod_vec_float(new.x, prod_scal_vec(new.x, z_axis));
		new.z = normalise(sous_vec_vec(z_axis, new.z));
	}
	new.y = normalise(prod_vec_vec(new.z, new.x));
	return (new);
}

/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the z axis.
 *
 * @param t_vector z_orientation	-> the new basis' z axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
static t_basis	get_ortho_basis_from_z(t_vector z_orientation)
{
	t_vector	y_axis;
	t_basis		new;

	new.z = normalise(z_orientation);
	y_axis = (t_vector){0, 1, 0};
	if (z_orientation.x == 0.0f && z_orientation.y == 1.0f
		&& z_orientation.z == 0.0f)
		new.y = (t_vector){0, 0, -1};
	else if (z_orientation.x == 0.0f && z_orientation.y == -1.0f
		&& z_orientation.z == 0.0f)
		new.y = (t_vector){0, 0, 1};
	else
	{
		new.y = prod_vec_float(new.z, prod_scal_vec(new.z, y_axis));
		new.y = normalise(sous_vec_vec(y_axis, new.y));
	}
	new.x = normalise(prod_vec_vec(new.y, new.z));
	return (new);
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
	if (to_set->type == LIGHT_OBJ)
		color_to_set = &to_set->special_data.light.color;
	*color_to_set = new_color;
	return (to_set);
}
