/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_prod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:29:11 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/09 00:20:21 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the product of a vector structure and an integer.
 *
 * @param t_vector a	-> vector to multiply
 * @param int k			-> integer to multiply
 * @return t_vector		-> the vecotr resulting from the multiplication
 */
t_vector	prod_vec_int(t_vector a, int k)
{
	t_vector	c;

	c.x = a.x * k;
	c.y = a.y * k;
	c.z = a.z * k;
	return (c);
}

/*
 * Function to return the scalar product of two vector structures.
 *
 * @param t_vector a	-> first vector of the product
 * @param t_vector b	-> second vector of the product
 * @return float		-> result of the scalar product
 */
float	prod_scal_vec(t_vector a, t_vector b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

/*
 * Function to return the scalar product of two coords structures.
 *
 * @param t_coords a	-> first coords of the product
 * @param t_coords b	-> second coords of the product
 * @return float		-> result of the scalar product
 */
float	prod_scal_coords(t_coords a, t_coords b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

/*
 * Function to return the scalar product of a vector structure and a coords
 * structure.
 *
 * @param t_vector a	-> vector structure as first factor of the product
 * @param t_coords b	-> coords structure as second factor of the product
 * @return float		-> result of the scalar product
 */
float	prod_scal_vec_coords(t_vector a, t_coords b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

/*
 * Function to return the cross product between two vector stuctures.
 *
 * @param t_vector a	-> vector structure as first factor of the product
 * @param t_coords b	-> coords structure as second factor of the product
 * @return t_vector		-> result of the cross product
 */
t_vector	prod_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
