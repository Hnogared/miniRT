/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:00 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/29 16:31:01 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

	t = (-b + sqrt(delta)) / (2 * a);
	if (t > 0)
		return (t);
	else
	{
		t = (-b - sqrt(delta)) / (2 * a);
		return (t);
	}
}
