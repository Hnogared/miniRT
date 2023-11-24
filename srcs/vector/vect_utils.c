/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:03:20 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/24 11:51:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	sous_vec_coord(t_coords a, t_coords b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vector	add_vec_coord(t_coords a, t_coords b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector	sous_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vector	add_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_coords	add_vec_coord_vec(t_coords a, t_vector b)
{
	t_coords	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector	prod_vec_int(t_vector a, int k)
{
	t_vector	c;

	c.x = a.x * k;
	c.y = a.y * k;
	c.z = a.z * k;
	return (c);
}

t_vector	prod_vec_float(t_vector a, float k)
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

t_coords	advance_on_vec(t_coords dep, t_vector dir, int k)
{
	t_coords	new;

	new.x = dep.x + k * dir.x;
	new.y = dep.y + k * dir.y;
	new.z = dep.z + k * dir.z;
	return (new);
}

t_coords	find_pos_touch(t_ray ray, float t)
{
	//P=O+t⋅D;
	t_coords	new_o;

	new_o.x = ray.origin_coords.x + t * ray.vector.x;
	new_o.y = ray.origin_coords.y + t * ray.vector.y;
	new_o.z = ray.origin_coords.z + t * ray.vector.z;
	return (new_o);
}

t_coords	give_coord(t_coords coord)
{
	t_coords	new_c;

	new_c.x = coord.x;
	new_c.y = coord.y;
	new_c.z = coord.z;

	return (new_c);
}

float	good_sol(float delta, float b, float a)
{
	float	t;

	t = (- b + sqrt(delta)) / (2 * a);
	if (t > 0)
		return (t);
	else
	{
		t = (- b - sqrt(delta)) / (2 * a);
		return (t);
	}
}

