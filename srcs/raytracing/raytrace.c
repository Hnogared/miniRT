/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:01:02 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 21:59:39 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to get the color resulting from the objects off which the parameter
 * ray bounced of.
 *
 * @param t_ray ray		-> the ray from which to return the bounces color
 * @return t_rgb_color	-> the color resulting from the objects bounces
 *
 * @parent_funct rotated_raytrace	-> function to trace a rotated ray
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

/*
 * Function to trace the parameter ray and return its resulting color after
 * rotating it around the parameter axis at the parameter angle.
 * Return a light's color, if it is the first object touched.
 * Return darkened ambient light if no object has been bounced off of.
 *
 * @param const t_data *data	-> pointer to teh data to use for tracing
 * @param t_ray ray				-> ray to rotate and trace
 * @param float angle			-> angle of the ray rotation
 * @param t_vector axis			-> axis around which to rotate the ray
 * @return t_rgb_color			-> the traced ray's resulting color
 *
 * @child_func get_reflections_color-> function to get a ray's reflections color
 * @parent_func diffuse_raytracing	-> function to average out multiple rays
 * @parent_func raytrace			-> function to trace and return a ray color
 */
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

/*
 * Function to trace 4 diagonally spread out rays from the parameter ray and
 * return their average.
 *
 * @param const t_data *data	-> pointer to the data to use for tracing
 * @param t_ray ray				-> origin ray from which to trace the 4 others
 * @return size_t				-> the average color between the spread out rays
 *
 * @parent_func raytrace	-> function to trace a ray and return its color
 */
static size_t	diffuse_raytracing(const t_data *data, t_ray ray)
{
	size_t		new_rgb[3];
	t_rgb_color	res_color;
	t_vector	angle_vect;

	angle_vect = axial_vector_rotation(ray.local_basis.y, 45.0f,
			ray.local_basis.x);
	res_color = rotated_raytrace(data, ray, 0.03f, angle_vect);
	new_rgb[0] = res_color.red;
	new_rgb[1] = res_color.green;
	new_rgb[2] = res_color.blue;
	res_color = rotated_raytrace(data, ray, -0.03f, angle_vect);
	new_rgb[0] += res_color.red;
	new_rgb[1] += res_color.green;
	new_rgb[2] += res_color.blue;
	angle_vect = axial_vector_rotation(ray.local_basis.y, -45.0f,
			ray.local_basis.x);
	res_color = rotated_raytrace(data, ray, 0.03f, angle_vect);
	new_rgb[0] += res_color.red;
	new_rgb[1] += res_color.green;
	new_rgb[2] += res_color.blue;
	res_color = rotated_raytrace(data, ray, -0.03f, angle_vect);
	new_rgb[0] += res_color.red;
	new_rgb[1] += res_color.green;
	new_rgb[2] += res_color.blue;
	return ((new_rgb[0] / 4) << 16 | (new_rgb[1] / 4) << 8 | new_rgb[2] / 4);
}

/*
 * Function to trace the parameter ray and return the color resulting of its
 * bounces.
 * If the anti aliasing boolean is set to true, traces 4 diagonally spread out
 * rays from the parameter ray and returns their average.
 *
 * @param const t_data *data	-> pointer to the data to use for tracing
 * @param t_ray ray				-> the ray to trace
 * @param bool anti_aliasing	-> enables anti aliasing if true
 * @return size_t				-> the calculated ray color
 *
 * @child_func diffuse_raytracing	-> function to average out multiple rays
 * @child_func rotated_raytrace		-> function to trace a rotated ray
 */
size_t	raytrace(const t_data *data, t_ray ray, bool anti_aliasing)
{
	if (anti_aliasing)
		return (diffuse_raytracing(data, ray));
	return (rgb_to_sizet(rotated_raytrace(data, ray, 0, (t_vector){0, 0, 0})));
}
