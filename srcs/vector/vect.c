/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/13 12:59:05 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to trace a ray, check if it touches the parameter object and update
 * it if true.
 *
 * @param t_ray *ray	-> pointer to the ray to test and update
 * @param t_object obj	-> object to check the collision with
 * @param int i			-> objects array index of the object structure
 */
int	do_touch(t_ray *ray, t_object obj, int i)
{
	if (obj.type == SPHERE_OBJ)
		try_sphere(ray, obj, i);
	else if (obj.type == PLANE_OBJ)
		try_plane(ray, obj, i);
	else if (obj.type == CYLINDER_OBJ)
		try_cylinder(ray, obj, i);
	else if (obj.type == LIGHT_OBJ)
		try_light(ray, obj, i);
	return (0);
}

/*
 * Function to trace a ray and update it according to the results of it touching
 * an object of the scene or not.
 * If the ray doesn't touch any object, its variable 'touch' is set to 0.
 * If the ray touches one or more objects, the closest object is saved inside its
 * 'objects_touch' array, its coordinates are set to their intersection point,
 * its vector is reflected on it and its 'light_color' variable is set to the
 * result of the shadow ray starting from the intersection point.
 *
 * @param const t_data *data	-> pointer to the program data to read from
 * @param t_ray *ray			-> pointer to the ray to trace and update
 *
 * @parent_function ray_advance	-> function to trace and update a ray's bounces
 */
static void	touch_objects(const t_data *data, t_ray *ray)
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
	ray->vector = get_reflection_vector(*ray, data->scene_objects[ray->go]);
	ray->origin_coords = ray->coords;
	ray->touch = 1;
	ray->nb_ref++;
	ray->objects_touch[ray->s++] = data->scene_objects[ray->go];
}

/*
 * Function to trace a ray for RT_MAX_BOUNCES maximum amount of bounces on scene
 * objects and update it according to the objects it bounced off of.
 * If no objects are touched, the ray's 'touch' variable is set to 0.
 * If one or more objects are touched, they are stored inside the ray's
 * 'objects_touch' array and the result from the shadow ray with the first object
 * bounce is saved inside its 'light_color' variable.
 *
 * @param const t_data *data	-> pointer to the program data to read from
 * @param t_ray *ray			-> pointer to the ray to trace and update
 *
 * @child_func touch_objects	-> function to update a ray's object bounce
 */
void	ray_advance(const t_data *data, t_ray *ray)
{
	ray->touch = 1;
	ray->nb_ref = 0;
	ray->tl = 0;
	ray->s = 0;
	while (ray->touch != 0 && ray->nb_ref < RT_MAX_BOUNCES && ray->tl == 0)
	{
		ray->res = 0;
		ray->sol = -1;
		ray->go = -1;
		touch_objects(data, ray);
	}
}
