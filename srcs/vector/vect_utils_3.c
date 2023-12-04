/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:29:17 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/29 16:29:19 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	calc_ref_form(t_vector i, t_vector n)
{
	t_vector	r;
	float		scal;

	scal = prod_scal_vec(i, n);
	r = sous_vec_vec(i, prod_vec_int(n, 2 * scal));
	return (r);
}

float	magnitude(t_vector n)
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

float	magnitude_coord(t_coords n)
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

t_vector	normalise(t_vector n)
{
	float		a;
	t_vector	nn;

	a = magnitude(n);
	if (a == 1)
		return (n);
	else
	{
		nn.x = n.x / a;
		nn.y = n.y / a;
		nn.z = n.z / a;
		return (nn);
	}
}

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
