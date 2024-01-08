/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_add_subs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:03:20 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/09 00:09:13 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the substraction of two coords structures as a vector.
 *
 * @param t_coords a	-> coords structure from which to substract
 * @param t_coords b	-> coords structure to substract
 * @return t_vector		-> the vector resulting from the substraction
 */
t_vector	subs_vec_coords(t_coords a, t_coords b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

/*
 * Function to return the addition of two coords structures as a vector.
 *
 * @param t_coords a	-> coords structure to add to
 * @param t_coords b	-> coords structure to add
 * @return t_vector		-> the vector resulting from the addition
 */
t_vector	add_vec_coords(t_coords a, t_coords b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

/*
 * Function to return the substraction of two vector structures as a vector.
 *
 * @param t_vector a	-> vector structure from which to substract
 * @param t_vector b	-> vector structure to substract
 * @return t_vector		-> the vector resulting from the substraction
 */
t_vector	subs_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

/*
 * Function to return the addition of two vector structures as a vector.
 *
 * @param t_vector a	-> vector structure to add to
 * @param t_vector b	-> vector structure to add
 * @return t_vector		-> the vector resulting from the addition
 */
t_vector	add_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

/*
 * Function to return the addition of a coords structure and a vector structure
 * as a coords structure.
 *
 * @param t_coords a	-> coords structure to add to
 * @param t_vector b	-> vector structure to add
 * @return t_coords		-> the coords resulting from the addition
 */
t_coords	add_vec_coord_vec(t_coords a, t_vector b)
{
	t_coords	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}
