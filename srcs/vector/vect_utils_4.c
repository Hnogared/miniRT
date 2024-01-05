/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:31:00 by tlorne            #+#    #+#             */
/*   Updated: 2023/12/18 15:15:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coords	find_pos_touch(t_ray *ray, float t)
{
	t_coords	new_o;

	new_o.x = ray->origin_coords.x + t * ray->vector.x;
	new_o.y = ray->origin_coords.y + t * ray->vector.y;
	new_o.z = ray->origin_coords.z + t * ray->vector.z;
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

void	print_vec(t_vector vec)
{
	printf("x vaut : %f\n", vec.x);
	printf("y vaut : %f\n", vec.y);
	printf("z vaut : %f\n", vec.z);
}

void	print_coord(t_coords cor)
{
	printf("x vaut : %f\n", cor.x);
	printf("y vaut : %f\n", cor.y);
	printf("z vaut : %f\n", cor.z);
}
