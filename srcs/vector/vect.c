/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2023/12/01 17:26:36 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	do_touch(t_ray ray, t_object obj)
{
	if (obj.type == SPHERE_OBJ)
		return (try_sphere(ray, obj));
	else if (obj.type == PLANE_OBJ)
		return (try_plan(ray, obj));
	else if (obj.type == CYLINDER_OBJ)
		return (try_cylinder_side(ray, obj));
	else
		return (0);
}

//ray.objects_touch[ray.s++] = NULL;
void	touch_object(t_data *data, t_ray ray)
{
	unsigned short	i;
	int				res;

	i = 0;
	while (i < data->obj_count)
	{
		res = do_touch(ray, data->scene_objects[i]);
		printf("res vaut %d\n", res);
		if (res >= 1)
		{
			ray->vector = calcul_ref(ray, data->scene_objects[i], res);
			ray->origin_coords = give_coord(ray->coords);
			ray->touch = 1;
			ray->nb_ref++;
			ray->objects_touch[ray->s++] = data->scene_objects[i];
			return ;
		}
		i++;
	}
	ray.touch = 0;
	return ;
}

void	ray_advance(t_data *data, t_ray *ray)
{
	ray->touch = 1;
	ray->nb_ref = 0;
	ray->s = 0;
	ray->objects_touch = malloc(sizeof(t_object) * 4);
	while (ray->touch != 0 && ray->nb_ref <= 2)
		touch_object(data, ray);
	printf("** %d ** ", ray->nb_ref);
	print_vector(ray->vector);
	printf(" ");
	print_coords(ray->origin_coords);
	printf("\n");
}
