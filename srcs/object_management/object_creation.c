/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 15:23:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
