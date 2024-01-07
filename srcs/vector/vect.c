/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/07 00:39:50 by hnogared         ###   ########.fr       */
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
		try_cylinder(ray, obj, i);
	else if (obj.type == LIGHT_OBJ)
		try_light(ray, obj, i);
	return (0);
}

static void	touch_object(const t_data *data, t_ray *ray)
{
	unsigned short	i;

	i = 0;
	while (i < data->obj_count)
	{
		if (ray->s == 0
			|| data->scene_objects[i].id != ray->objects_touch[ray->s - 1].id)
			do_touch(ray, data->scene_objects[i], i);
		i++;
	}
	ray->touch = 0;
	if (ray->res < 1)
		return ;
	if (!ray->nb_ref)
	{
		ray->light_color = shadow_ray(ray->coords, data->scene_objects,
				data->obj_count, data->ambient_l);
	}
	ray->vector = calcul_ref(ray, data->scene_objects[ray->go], ray->res);
	ray->origin_coords = ray->coords;
	ray->touch = 1;
	ray->nb_ref++;
	ray->objects_touch[ray->s++] = data->scene_objects[ray->go];
}

void	ray_advance(const t_data *data, t_ray *ray)
{
	ray->touch = 1;
	ray->nb_ref = 0;
	ray->tl = 0;
	ray->s = 0;
	while (ray->touch != 0 && ray->nb_ref <= RT_MAX_BOUNCES - 1 && ray->tl == 0)
	{
		ray->res = 0;
		ray->sol = -1;
		ray->go = -1;
		touch_object(data, ray);
	}
}
