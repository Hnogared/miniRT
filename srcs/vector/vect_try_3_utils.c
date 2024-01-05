/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try_3_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:35:35 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/05 15:35:36 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	test(t_ray aligned_ray, t_object obj)
{
	if (aligned_ray.coords.z
		<= (obj.coords.z + obj.special_data.cylinder.height / 2)
		&& aligned_ray.coords.z
		>= (obj.coords.z - obj.special_data.cylinder.height / 2))
	{
		return (1);
	}
	else
		return (0);
}

void	give_sol(t_ray *aligned_ray, float t, int i)
{
	aligned_ray->sol = t;
	aligned_ray->res = 3;
	aligned_ray->go = i;
}

t_ray	switch_rb(t_ray *ray, t_object obj)
{
	t_ray	aligned_ray;

	aligned_ray = switch_ray_basis(*ray, obj.local_basis,
			(t_basis){{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
	return (aligned_ray);
}

t_coords	switch_cb(t_object obj)
{
	obj.coords = switch_coords_basis(obj.coords, obj.local_basis,
			(t_basis){{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
	return (obj.coords);
}
