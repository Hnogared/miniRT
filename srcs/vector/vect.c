/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/05 00:48:39 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	do_touch(t_ray *ray, t_object obj, int i)
{
	if (obj.type == SPHERE_OBJ)
		try_sphere(ray, obj, i);
	else if (obj.type == PLANE_OBJ)
		try_plan(ray, obj, i);
	else if (obj.type == CYLINDER_OBJ)
		try_cylinder_side(ray, obj, i);
	else if (obj.type == LIGHT_OBJ)
		try_light(ray, obj, i);
	return (0);
}

void	init_ray(t_ray *ray)
{
	ray->res = 0;
	ray->sol = -1;
	ray->go = -1;
	return ;
}

void	touch_object(const t_data *data, t_ray *ray)
{
	unsigned short	i;

	i = 0;
	init_ray(ray);
	while (i < data->obj_count)
	{
		if (data->scene_objects[i].id != ray->objects_touch[ray->s - 1].id)
			do_touch(ray, data->scene_objects[i], i);
		i++;
	}
	if (ray->res >= 1)
	{
		if (!ray->nb_ref)
			ray->light_color = shadow_ray(ray->coords, data->scene_objects,
					data->obj_count, data->ambient_l);
		ray->vector = calcul_ref(ray, data->scene_objects[ray->go], ray->res);
		ray->origin_coords = ray->coords;
		ray->touch = 1;
		ray->nb_ref++;
		ray->objects_touch[ray->s++] = data->scene_objects[ray->go];
		return ;
	}
	ray->touch = 0;
	return ;
}

void	ray_advance(const t_data *data, t_ray *ray)
{
	ray->touch = 1;
	ray->nb_ref = 0;
	ray->tl = 0;
	ray->s = 0;
	ray->sol = -1;
	while (ray->touch != 0 && ray->nb_ref <= RT_MAX_BOUNCES - 1 && ray->tl == 0)
		touch_object(data, ray);
}
