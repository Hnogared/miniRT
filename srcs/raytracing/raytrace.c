/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:01:02 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/07 16:14:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	rgb_to_uint(t_rgb_color color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}

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
//	int				i;

	if (ray.objects_touch[0].type == LIGHT_OBJ)
		return (0xFFFFFF);
	objects = ray.objects_touch;
	color = rgb_color_mix(objects[0].ft_get_color(objects[0].special_data),
			ambient_l.color, ambient_l.ratio);
//	i = 1;
//	while (i < ray.nb_ref)
//	{
//		if (objects[i].type == LIGHT_OBJ)
//		{
//			color = rgb_color_mix(color, (t_rgb_color){0xFF, 0xFF, 0xFF},
//					objects[i].special_data.light.brightness);
//			break ;
//		}
///		color = rgb_color_mix(color,
//				objects[i].ft_get_color(objects[i].special_data), 0.5f);
//		i++;
//	}
	return (rgb_to_uint(color));
}

size_t	raytrace(t_data *data, int x, int y)
{
	ray_advance(data, &data->view_rays[y][x]);
	if (data->view_rays[y][x].nb_ref)
	{
		return (get_reflections_color(data->ambient_l, data->view_rays[y][x]));
	}
	return (rgb_to_uint(rgb_color_mix((t_rgb_color){0, 0, 0},
			data->ambient_l.color, data->ambient_l.ratio)));
}

t_rgb_color	rgb_color_mix(t_rgb_color color1, t_rgb_color color2, float ratio)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (color1.red + (float) color2.red * ratio) / 2;
	green = (color1.green + (float) color2.green * ratio) / 2;
	blue = (color1.blue + (float) color2.blue * ratio) / 2;
	return ((t_rgb_color){red, green, blue});
}
