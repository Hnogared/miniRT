/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:16:55 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/13 20:16:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_rgb_color	advance_shadow_ray(t_ray *shadow_ray,
	t_object *objects_array, unsigned short objects_count, int touched_obj_id)
{
	int			i;
	float		strength;
	t_object	light;

	i = -1;
	touched_obj_id++;
	while (++i < (int) objects_count)
		do_touch(shadow_ray, objects_array[i], i);
	if (objects_array[shadow_ray->go].type != LIGHT_OBJ)
		return (shadow_ray->light_color);
	light = objects_array[shadow_ray->go];
	strength = light.special_data.light.brightness * 20 / shadow_ray->sol;
	shadow_ray->light_color = rgb_color_lighten(shadow_ray->light_color,
			light.special_data.light.color, strength);
	return (shadow_ray->light_color);
}

t_rgb_color	shadow_ray(t_coords start_coords, t_object *objects_array,
	unsigned short objects_count, int touched_obj_id)
{
	int		i;
	t_ray	shadow_ray;

	shadow_ray = new_ray((t_basis){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
			start_coords);
	shadow_ray.light_color = (t_rgb_color){0, 0, 0};
	i = -1;
	while (++i < objects_count)
	{
		if (objects_array[i].type != LIGHT_OBJ)
			continue ;
		shadow_ray.vector = normalise(sous_vec_coord(objects_array[i].coords,
					start_coords));
		shadow_ray.sol = -1;
		advance_shadow_ray(&shadow_ray, objects_array, objects_count,
			touched_obj_id);
	}
	return (shadow_ray.light_color);
}
