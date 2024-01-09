/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:00 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/09 00:24:56 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
 * Function to return true if two vectors are the same, false otherwise.
 *
 * @param t_vector vector1	-> the first vector structure to compare
 * @param t_vector vector2	-> the second vector structure to compare
 * @return bool				-> the result of the comparison
 */
bool	is_vector_equal(t_vector vector1, t_vector vector2)
{
	return (vector1.x == vector2.x && vector1.y == vector2.y
		&& vector1.z == vector2.z);
}

float	to_rad(float degree_angle)
{
	return ((degree_angle * M_PI) / 180);
}

float	good_sol(float delta, float b, float a)
{
	float	t1;
	float	t2;

	t1 = (-b + sqrt(delta)) / (2 * a);
	if (!delta)
		return (t1);
	t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
		return (ft_fmin(t1, t2));
	if (t1 >= 0)
		return (t1);
	return (t2);
}

t_coords	find_pos_touch(t_ray *ray, float t)
{
	t_coords	new_o;

	new_o.x = ray->origin_coords.x + t * ray->vector.x;
	new_o.y = ray->origin_coords.y + t * ray->vector.y;
	new_o.z = ray->origin_coords.z + t * ray->vector.z;
	return (new_o);
}

t_vector	prod_vec_float(t_vector a, float k)
{
	t_vector	c;

	c.x = a.x * k;
	c.y = a.y * k;
	c.z = a.z * k;
	return (c);
}
