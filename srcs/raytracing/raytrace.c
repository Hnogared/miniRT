/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:01:02 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 01:02:33 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	test_grid(__attribute__((unused)) const t_data *data, int x, int y)
{
	return (x << 16 | (y | x) << 8);
}

/*
 *
 */
static t_rgb_color	get_reflections_color(t_ray ray)
{
	t_rgb_color		color;
	t_object		*objects;
	int				i;

	objects = ray.objects_touch;
	color = rgb_color_mix(objects[0].ft_get_color(objects[0].special_data),
			(t_rgb_color){0, 0, 0}, 0.3f);
	i = 1;
	while (i < ray.nb_ref)
	{
		if (objects[i].type == LIGHT_OBJ)
		{
			return (rgb_color_lighten(color,
					objects[i].special_data.light.color,
					objects[i].special_data.light.brightness));
		}
		color = rgb_color_mix(color,
				objects[i].ft_get_color(objects[i].special_data), 0.3f);
		i++;
	}
	return (color);
}

static t_rgb_color	rotated_raytrace(const t_data *data, t_ray ray, float angle,
	t_vector axis)
{
	t_rgb_color	ray_color;

	if (angle != 0.0f)
		ray.vector = axial_vector_rotation(ray.vector, angle, axis);
	ray_advance(data, &ray);
	if (ray.objects_touch[0].type == LIGHT_OBJ)
		return (ray.objects_touch[0].special_data.light.color);
	if (ray.nb_ref)
		ray_color = get_reflections_color(ray);
	else
	{
		return (rgb_color_lighten((t_rgb_color){0, 0, 0}, data->ambient_l.color,
			data->ambient_l.ratio));
	}
	return (rgb_color_lighten(ray_color, ray.light_color, 1.0f));
}

size_t	raytrace(const t_data *data, t_ray ray, bool anti_aliasing)
{
	size_t		new_rgb[3];
	t_rgb_color	res_color;

	if (!anti_aliasing)
	{
		return (rgb_to_sizet(rotated_raytrace(data, ray, 0,
					(t_vector){0, 0, 0})));
	}
	res_color = rotated_raytrace(data, ray, 0.05f, ray.local_basis.y);
	new_rgb[0] = res_color.red;
	new_rgb[1] = res_color.green;
	new_rgb[2] = res_color.blue;
	res_color = rotated_raytrace(data, ray, -0.05f, ray.local_basis.y);
	new_rgb[0] += res_color.red;
	new_rgb[1] += res_color.green;
	new_rgb[2] += res_color.blue;
	res_color = rotated_raytrace(data, ray, 0.05f, ray.local_basis.z);
	new_rgb[0] += res_color.red;
	new_rgb[1] += res_color.green;
	new_rgb[2] += res_color.blue;
	res_color = rotated_raytrace(data, ray, -0.05f, ray.local_basis.z);
	new_rgb[0] += res_color.red;
	new_rgb[1] += res_color.green;
	new_rgb[2] += res_color.blue;
	return ((new_rgb[0] / 4) << 16 | (new_rgb[1] / 4) << 8 | new_rgb[2] / 4);
}
