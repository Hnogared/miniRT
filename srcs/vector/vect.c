/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2023/12/14 11:59:32 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	do_touch(t_ray *ray, t_object obj, int i)
{
	//printf("%d\n", obj.type);
	//printf("avant try, vecteur ray vaut :\n");
	//print_vec(ray->vector);
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

//ray.objects_touch[ray.s++] = NULL;
void	touch_object(const t_data *data, t_ray *ray)
{
	unsigned short	i;
	//int				res;

	i = 0;
	ray->res = 0;
	ray->sol = -1;
	ray->go = -1;
	while (i < data->obj_count)
	{
		do_touch(ray, data->scene_objects[i], i);
		//res == i;
		//if (res == 2 || res == 3)
		//	printf("res vaut %d\n", res);
		//if (res == 1)
		//	printf("res vaut %d\n", res);
		//if (res == 0)
		//	printf("-0");
		//if (res == 1)
		//	printf("-C");
		//if (res == 2 || res == 3)
		//	printf("-E");
		//printf("%d-", ray->res);
		//ray->res = res;
		//printf("sol = %f et res vaut : %d --", ray->sol, ray->res);
		
		i++;
	}
	if (ray->res >= 1)
	{
		//printf("sol = %f et res vaut : %d --", ray->sol, ray->res);
		//printf("%d-", ray->res);
		//printf("ca touche !!!!!!!!\n");
		//printf("avant changement, vecteur rayon vaut\n");
		//print_vec(ray->vector);
		if (!ray->nb_ref)
		{
			ray->light_color = shadow_ray(ray->coords, data->scene_objects,
					data->obj_count);
		}
		ray->vector = calcul_ref(ray, data->scene_objects[ray->go], ray->res);
		//printf("apres changement, vecteur rayon vaut\n");
		//print_vec(ray->vector);
		ray->origin_coords = ray->coords;
		ray->touch = 1;
		ray->nb_ref++;
		/*if (res == 1)
		{
			printf("res vaut %d\n", res);
			printf("nb_ref vaut %d\n", ray->nb_ref);
		}*/
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
//	ray->objects_touch = malloc(sizeof(t_object) * 4);
	//printf("avant tentative de touch, veteur ray vaut :\n");
	//print_vec(ray->vector);
	while (ray->touch != 0 && ray->nb_ref <= RT_MAX_BOUNCES - 1 && ray->tl == 0)
		touch_object(data, ray);
	//printf("ok\n");
	/*printf("** %d ** ", ray->nb_ref);
	print_vector(ray->vector);
	printf(" ");
	print_coords(ray->origin_coords);
	printf("\n");*/
}
