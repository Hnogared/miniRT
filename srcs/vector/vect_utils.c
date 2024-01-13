/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:29:17 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/13 11:24:02 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the magnitude of a vector.
 *
 * @param t_vector vector	-> vector structure to get the magnitude from
 * @return float			-> magnitude of the vector
 */
float	magnitude(t_vector vector)
{
	float	nxc;
	float	nyc;
	float	nzc;

	nxc = pow(vector.x, 2);
	nyc = pow(vector.y, 2);
	nzc = pow(vector.z, 2);
	return (sqrt(nxc + nyc + nzc));
}

/*
 * Function to return the magnitude of coordinates.
 *
 * @param t_coords coords	-> coords structure to get the magnitude from
 * @return float			-> magnitude of the coordinates
 */
float	magnitude_coords(t_coords coords)
{
	float	nxc;
	float	nyc;
	float	nzc;

	nxc = pow(coords.x, 2);
	nyc = pow(coords.y, 2);
	nzc = pow(coords.z, 2);
	return (sqrt(nxc + nyc + nzc));
}

/*
 * Function to get the distance between two coords structures.
 *
 * @param t_coords a	-> first coordinates of the distance calculation
 * @param t_coords b	-> second coordinates of the distance calculation
 * @return float		-> distance between the two coordinates.
 */
float	dist(t_coords a, t_coords b)
{
	float	x;
	float	y;
	float	z;

	x = pow((b.x - a.x), 2);
	y = pow((b.y - a.y), 2);
	z = pow((b.z - a.z), 2);
	return (sqrt(x + y + z));
}

/*
 * Function to normalise a vector, which means setting its magnitude to 1 while
 * keeping its orientation.
 *
 * @param t_vector vector	-> vector to normalize
 * @return t_vector			-> normalized vector
 */
t_vector	normalise(t_vector vector)
{
	float		a;
	t_vector	normalized;

	a = magnitude(vector);
	if (a == 1)
		return (vector);
	normalized.x = vector.x / a;
	normalized.y = vector.y / a;
	normalized.z = vector.z / a;
	return (normalized);
}

/*
 * Function to return the reflection of an incident vector relative to a normal
 * vector.
 *
 * @param t_vector incident_vec	-> the incident vector to reflect
 * @param t_vector normal_vec	-> the normal vector for the reflection direction
 * @return t_vector				-> the vector resulting from the reflection
 */
t_vector	calc_ref_form(t_vector incident_vec, t_vector normal_vec)
{
	float		scal;

	scal = prod_scal_vec(incident_vec, normal_vec);
	return (subs_vec_vec(incident_vec, prod_vec_float(normal_vec, 2 * scal)));
}
