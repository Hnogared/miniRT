/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:01:02 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/09 21:41:52 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	test_grid(t_data *data, int x, int y)
{
	data = data;
	return (x << 16 | (y | x) << 8);
}

static size_t	get_reflections_color(t_ambient_light ambient_l, t_ray ray)
{
	t_rgb_color		color;
	t_object		*objects;
	int				i;

	if (ray.objects_touch[0].type == LIGHT_OBJ)
		return (0xFFFFFF);
	objects = ray.objects_touch;
	color = rgb_color_mix(objects[0].ft_get_color(objects[0].special_data),
			ambient_l.color, ambient_l.ratio);
	i = 1;
	while (i < ray.nb_ref)
	{
		if (objects[i].type == LIGHT_OBJ)
		{
			color = rgb_color_mix(color, (t_rgb_color){0xFF, 0xFF, 0xFF},
					objects[i].special_data.light.brightness);
			break ;
		}
		color = rgb_color_mix(color,
				objects[i].ft_get_color(objects[i].special_data), 0.2f);
		i++;
	}
	return (rgb_to_sizet(color));
}

static t_vector	random_vector_rotation(t_vector to_rotate, t_basis basis,
	float degrees_angle)
{
	float		num;
	t_vector	new_vector;

	num = (float)(rand() % 101 - 50 % 51) / 50;
	new_vector = axial_vector_rotation(to_rotate, num * degrees_angle, basis.z);
	num = (float)(rand() % 101 - 50 % 51) / 50;
	new_vector = axial_vector_rotation(new_vector, num * degrees_angle, basis.y);
	return (normalise(new_vector));
}

size_t	raytrace(t_data *data, t_ray ray, bool random)
{
	if (random == true)
		ray.vector = random_vector_rotation(ray.vector, ray.local_basis, 0.05f);
	ray_advance(data, &ray);
	if (ray.nb_ref)
		return (get_reflections_color(data->ambient_l, ray));
	return (rgb_to_sizet(rgb_color_mix((t_rgb_color){0, 0, 0},
		data->ambient_l.color, data->ambient_l.ratio)));
}
