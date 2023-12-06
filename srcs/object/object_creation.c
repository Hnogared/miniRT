/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/06 11:27:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to initialize a camera object.
 * The camera will be initialized to zero except for its coords and fov.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the camera's coords to set
 * @param int fov			-> the camera's fov to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_camera(t_object *to_set, t_coords coords, int fov)
{
	if (!to_set)
		return (NULL);
	to_set->type = CAMERA_OBJ;
	to_set->has_color = false;
	set_object_coords(to_set, coords);
	set_object_orientation(to_set, (t_vector){0, 0, 0});
	to_set->special_data.camera.fov = fov;
	to_set->ft_get_color = &get_uncolored_color;
	to_set->ft_print_data = &print_camera_data;
	return (to_set);
}

/*
 * Function to initialize a light object.
 * The light will be initialized to zero except for its coords and brightness.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the light's coords to set
 * @param int brightness	-> the light's brightness to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_light(t_object *to_set, t_coords coords, float brightness)
{
	if (!to_set)
		return (NULL);
	to_set->type = LIGHT_OBJ;
	to_set->has_color = false;
	set_object_coords(to_set, coords);
	set_object_orientation(to_set, (t_vector){0, 0, 0});
	to_set->special_data.light.brightness = brightness;
	to_set->ft_get_color = &get_uncolored_color;
	to_set->ft_print_data = &print_light_data;
	return (to_set);
}

/*
 * Function to initialize a sphere object.
 * The sphere will be initialized to zero except for its coords, diameter and
 * radius, which is calculated from the parameter diameter.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the sphere's coords to set
 * @param float diameter	-> the sphere's diameter to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_sphere(t_object *to_set, t_coords coords, float diameter)
{
	if (!to_set)
		return (NULL);
	to_set->type = SPHERE_OBJ;
	to_set->has_color = true;
	set_object_coords(to_set, coords);
	set_object_orientation(to_set, (t_vector){0, 0, 0});
	to_set->special_data.sphere.diameter = diameter;
	to_set->special_data.sphere.radius = diameter / 2;
	to_set->ft_get_color = &get_sphere_color;
	to_set->ft_print_data = &print_sphere_data;
	return (to_set);
}

/*
 * Function to initialize a plane object.
 * The plane will be initialized to zero except for its coords.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the plane's coords to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_plane(t_object *to_set, t_coords coords)
{
	if (!to_set)
		return (NULL);
	to_set->type = PLANE_OBJ;
	to_set->has_color = true;
	set_object_coords(to_set, coords);
	set_object_orientation(to_set, (t_vector){0, 0, 0});
	to_set->ft_get_color = &get_plane_color;
	to_set->ft_print_data = &print_plane_data;
	return (to_set);
}

/*
 * Function to initialize a cylinder object.
 * The cylinder will be initialized to zero except for its coords, diameter and
 * height.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the cylinder's coords to set
 * @param float diameter	-> the cylinder's diameter to set
 * @param float height		-> the cylinder's height to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_cylinder(t_object *to_set, t_coords coords, float diameter,
	float height)
{
	if (!to_set)
		return (NULL);
	to_set->type = CYLINDER_OBJ;
	to_set->has_color = true;
	set_object_coords(to_set, coords);
	set_object_orientation(to_set, (t_vector){0, 0, 0});
	to_set->special_data.cylinder.diameter = diameter;
	to_set->special_data.cylinder.height = height;
	to_set->ft_get_color = &get_cylinder_color;
	to_set->ft_print_data = &print_cylinder_data;
	return (to_set);
}
