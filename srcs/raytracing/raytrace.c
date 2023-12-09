/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:01:02 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/09 19:20:18 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	test_grid(t_data *data, int x, int y)
{
	int	color;

	color = *(int *)(unsigned char [4]){0, x, y | x, 0};
	data = data;
	return (color);
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

size_t	raytrace(t_data *data, t_ray ray)
{
	ray_advance(data, &ray);
	if (ray.nb_ref)
		return (get_reflections_color(data->ambient_l, ray));
	return (rgb_to_sizet(rgb_color_mix((t_rgb_color){0, 0, 0},
			data->ambient_l.color, data->ambient_l.ratio)));
}
