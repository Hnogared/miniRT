/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:29:11 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/29 16:29:12 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	prod_vec_int(t_vector a, int k)
{
	t_vector	c;

	c.x = a.x * k;
	c.y = a.y * k;
	c.z = a.z * k;
	return (c);
}

float	prod_scal_vec(t_vector a, t_vector b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

float	prod_scal_coord(t_coords a, t_coords b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

float	prod_scal_vec_coord(t_vector a, t_coords b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}

t_vector	prod_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
