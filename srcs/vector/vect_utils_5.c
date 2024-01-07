/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:05:57 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/07 22:05:10 by hnogared         ###   ########.fr       */
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

t_vector	prod_vec_float(t_vector a, float k)
{
	t_vector	c;

	c.x = a.x * k;
	c.y = a.y * k;
	c.z = a.z * k;
	return (c);
}
