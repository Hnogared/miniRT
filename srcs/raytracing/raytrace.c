/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:01:02 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/12 09:57:02 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	test_grid(t_data *data, int x, int y)
{
	data = data;
	return (x << 16 | (y | x) << 8);
}

static t_rgb_color	get_reflections_color(t_ambient_light ambient_l, t_ray ray)
{
	t_rgb_color		color;
	t_object		*objects;
	int				i;

	if (ray.objects_touch[0].type == LIGHT_OBJ)
		return ((t_rgb_color){255, 255, 255});
	objects = ray.objects_touch;
	color = rgb_color_mix(objects[0].ft_get_color(objects[0].special_data),
			(t_rgb_color){0, 0, 0}, 0.2f);
	i = 1;
	while (i < ray.nb_ref)
	{
		if (objects[i].type == LIGHT_OBJ)
		{
			return (rgb_color_lighten(color, (t_rgb_color){0xFF, 0xFF, 0xFF},
				objects[i].special_data.light.brightness));
		}
		color = rgb_color_mix(color,
				objects[i].ft_get_color(objects[i].special_data), 0.2f);
		i++;
	}
	return (rgb_color_lighten(color, ambient_l.color, ambient_l.ratio));
}

static t_rgb_color	rotated_raytrace(t_data *data, t_ray ray, float angle,
	t_vector axis)
{
	ray.vector = axial_vector_rotation(ray.vector, angle, axis);
	ray_advance(data, &ray);
	if (ray.nb_ref)
		return (get_reflections_color(data->ambient_l, ray));
	return (rgb_color_lighten((t_rgb_color){0, 0, 0}, data->ambient_l.color,
		data->ambient_l.ratio));
}

size_t	raytrace(t_data *data, t_ray ray)
{
	size_t		new_rgb[3];
	t_rgb_color	res_color;

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
