/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:00 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/13 11:46:11 by hnogared         ###   ########.fr       */
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

/*
 * Function to convert a degrees angle in radians.
 *
 * @param float degree_angle	-> angle in degrees to convert
 * @return float				-> the converted radians angle
 */
float	to_rad(float degree_angle)
{
	return ((degree_angle * M_PI) / 180);
}

/*
 * Function to return the smallest positive solution of a quadratic equation for
 * which the delta has already been calculated if there is one, else return a
 * negative solution.
 * This is used when probing for intersections between a ray and an object.
 * The smallest positive solution would be the closest intersection with the
 * object following the ray, while the smallest negative solution would be the
 * closest intersection following the ray backwards (useful for trippy display).
 *
 * @param float delta	-> delta value of the quadratic equation to test
 * @param float b		-> second factor of the quadratic equation
 * @param float a		-> first factor of the quadratic equation
 * @return float		-> the found solution
 */
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

/*
 * Function to return the coordinates resulting from tracing a ray for a given
 * distance, starting from its origin coordinates.
 *
 * @param t_ray ray			-> ray to trace for shifting the coordinates
 * @param float distance	-> distance to travel following the ray
 * @return t_coords			-> the shifted coordinates
 */
t_coords	find_pos_touch(t_ray ray, float distance)
{
	t_coords	new_o;

	new_o.x = ray.origin_coords.x + distance * ray.vector.x;
	new_o.y = ray.origin_coords.y + distance * ray.vector.y;
	new_o.z = ray.origin_coords.z + distance * ray.vector.z;
	return (new_o);
}

/*
 * Function to return the product of a vector and a float as a vector.
 *
 * @param t_vector vector	-> vector to multiply to
 * @param float num			-> float to multiply with
 * @return t_vector			-> the vector resulting from the product
 */
t_vector	prod_vec_float(t_vector vector, float num)
{
	t_vector	res_vec;

	res_vec.x = vector.x * num;
	res_vec.y = vector.y * num;
	res_vec.z = vector.z * num;
	return (res_vec);
}
