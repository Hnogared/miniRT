/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 15:44:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*new_camera(t_object *to_set, t_coords *coords,
	t_vector *orientation_vector, int fov)
{
	if (!to_set)
		return (NULL);
	if (coords)
		to_set->coords = *coords;
	else
		ft_bzero(&to_set->coords, sizeof(t_coords));
	if (orientation_vector)
		to_set->orientation_vector = *orientation_vector;
	else
		ft_bzero(&to_set->orientation_vector, sizeof(t_vector));
	to_set->type = CAMERA_OBJ;
	to_set->special_data.camera.fov = fov;
	to_set->data_print_func = &print_camera_data;
	return (to_set);
}

t_object	*new_light(t_object *to_set, t_coords *coords,
	t_vector *orientation_vector, int brightness)
{
	if (!to_set)
		return (NULL);
	if (coords)
		to_set->coords = *coords;
	else
		ft_bzero(&to_set->coords, sizeof(t_coords));
	if (orientation_vector)
		to_set->orientation_vector = *orientation_vector;
	else
		ft_bzero(&to_set->orientation_vector, sizeof(t_vector));
	to_set->type = LIGHT_OBJ;
	to_set->special_data.light.brightness = brightness;
	to_set->data_print_func = &print_light_data;
	return (to_set);
}

t_object	*new_sphere(t_object *to_set, t_coords *coords,
	t_vector *orientation_vector, float diameter)
{
	if (!to_set)
		return (NULL);
	if (coords)
		to_set->coords = *coords;
	else
		ft_bzero(&to_set->coords, sizeof(t_coords));
	if (orientation_vector)
		to_set->orientation_vector = *orientation_vector;
	else
		ft_bzero(&to_set->orientation_vector, sizeof(t_vector));
	to_set->type = SPHERE_OBJ;
	to_set->special_data.sphere.diameter = diameter;
	to_set->special_data.sphere.radius = diameter / 2;
	to_set->data_print_func = &print_sphere_data;
	return (to_set);
}

t_object	*new_plane(t_object *to_set, t_coords *coords,
	t_vector *orientation_vector)
{
	if (!to_set)
		return (NULL);
	if (coords)
		to_set->coords = *coords;
	else
		ft_bzero(&to_set->coords, sizeof(t_coords));
	if (orientation_vector)
		to_set->orientation_vector = *orientation_vector;
	else
		ft_bzero(&to_set->orientation_vector, sizeof(t_vector));
	to_set->type = PLANE_OBJ;
	to_set->data_print_func = &print_plane_data;
	return (to_set);
}

t_object	*new_cylinder(t_object *to_set, t_coords *coords,
	t_vector *orientation_vector, float dimensions[2])
{
	if (!to_set)
		return (NULL);
	if (coords)
		to_set->coords = *coords;
	else
		ft_bzero(&to_set->coords, sizeof(t_coords));
	if (orientation_vector)
		to_set->orientation_vector = *orientation_vector;
	else
		ft_bzero(&to_set->orientation_vector, sizeof(t_vector));
	to_set->type = CYLINDER_OBJ;
	to_set->special_data.cylinder.diameter = dimensions[0];
	to_set->special_data.cylinder.height = dimensions[1];
	to_set->data_print_func = &print_cylinder_data;
	return (to_set);
}
