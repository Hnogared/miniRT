/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:16:55 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/13 12:23:22 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_rgb_color	send_shadow_ray(t_ray shadow_ray, t_object *objects_array,
	unsigned short objecst_count, int touched_object_id)
{
	j = -1;
	while (++j < objects_count)
	{
		if (j == touched_obj_id)
			continue ;
		do_touch(&shadow_ray, objects_array[j], j);
	}
	if (objects_array[shadow_ray.go].type != LIGHT_OBJ)
		continue ;
	strength = objects_array[shadow_ray.go].special_data.light.brightness
			/ (shadow_ray.sol / 10);
	light_color = rgb_color_lighten(light_color,
			(t_rgb_color){0xFF, 0xFF, 0xFF}, strength);
	return ();
}

t_rgb_color	shadow_ray(t_coords start_coords, t_object *objects_array,
	unsigned short objects_count, int touched_object_id)
{
	int			i;
	int			j;
	float		strength;
	t_rgb_color	light_color;
	t_vector	placeholder;
	t_vector	ray_vector;
	t_ray		shadow_ray;

	light_color = (t_rgb_color){0, 0, 0};
	placeholder = (t_vector){0, 0, 1};
	i = -1;
	while (++i < objects_count)
	{
		if (objects_array[i].type != LIGHT_OBJ)
			continue ;
		ray_vector = normalise(sous_vec_coord(objects_array[i].coords,
				start_coords));
		shadow_ray = new_ray((t_basis){ray_vector, placeholder, placeholder},
				start_coords);
		shadow_ray.sol = -1;
		shadow_ray.go = -1;
	}
	return (light_color);
}
