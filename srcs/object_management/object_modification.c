/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:10:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/24 11:47:51 by hnogared         ###   ########.fr       */
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
static t_vector	prod_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

static float	magnitude(t_vector n)
{
	float		a;
	float		nxc;
	float		nyc;
	float		nzc;

	nxc = pow(n.x, 2);
	nyc = pow(n.y, 2);
	nzc = pow(n.z, 2);
	a = sqrt(nxc + nyc + nzc);
	return (a);
}

static t_vector	sous_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
static t_vector	normalise(t_vector n)
{
	float	a;

	a = magnitude(n);
	if (a == 1)
		return (n);
	else
	{
		n.x = n.x / a;
		n.y = n.y / a;
		n.z = n.z / a;
		return (n);
	}
}

static float	prod_scal_vec(t_vector a, t_vector b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

static t_vector	prod_float_vec(float k, t_vector a) 
{
	t_vector	c;

	c.x = a.x * k;
	c.y = a.y * k;
	c.z = a.z * k;
	return (c);
}
*/

/*
 * TODO comment i'm tred
 * TODO add normalise to z
 * https://math.stackexchange.com/questions/180418/calculate-rotation-matrix-to-align-vector-a-to-vector-b-in-3d 
 * https://en.wikipedia.org/wiki/Vector_projection#Vector_rejection
 */
static t_local_axes	*set_local_axes(t_local_axes *to_set, t_vector orientation)
{
	t_vector	normal_orientation;

	if (!to_set)
		return (NULL);
		/*
	get_rotation_matrix(to_set->rotation_matrix, orientation,
		(t_vector){0, 0, 1});
	to_set->x = matrix_vector_rotation((t_vector){1, 0, 0},
		to_set->rotation_matrix);
	to_set->y = matrix_vector_rotation((t_vector){0, 1, 0},
		to_set->rotation_matrix);
	to_set->z = orientation;
	*/
	normal_orientation = normalise(orientation);
	to_set->z = normal_orientation;
	to_set->y = normalise(sous_vec_vec((t_vector){0, 1, 0},
		prod_float_vec(prod_scal_vec(normal_orientation, (t_vector){0, 1, 0}), normal_orientation)));
	to_set->x = normalise(prod_vec_vec(to_set->y, normal_orientation));
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
