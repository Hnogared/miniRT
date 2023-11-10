/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:28:41 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 13:58:26 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
void	print_object_data(t_object object)
{
	ft_printf("[Object data]\nCoords :\n");
	print_coords(object.coords);
	printf("Orientation vector :\n");
	print_vector(object.orientation_vector);
	ft_printf("\n");
	if (object.type == CAMERA_OBJ)
		print_camera_data(object.camera_data);
	if (object.type == LIGHT_OBJ)
		print_light_data(object.light_data);
	if (object.type == SPHERE_OBJ)
		print_sphere_data(object.sphere_data);
	if (object.type == PLANE_OBJ)
		print_plane_data(object.plane_data);
	if (object.type == CYLINDER_OBJ)
		print_cylinder_data(object.cylinder_data);
}
*/

void	print_object_data(t_object object)
{
	ft_printf("[Object data]\nCoords :\n");
	print_coords(object.coords);
	printf("Orientation vector :\n");
	print_vector(object.orientation_vector);
	ft_printf("\n");
	object.data_print_func(object.special_data);
}

void	print_coords(t_coords coords)
{
	printf("x = %f\n", coords.x);
	printf("y = %f\n", coords.y);
	printf("z = %f\n", coords.z);
}

void	print_vector(t_vector vector)
{
	printf("x = %f\n", vector.x);
	printf("y = %f\n", vector.y);
	printf("z = %f\n", vector.z);
}

void	print_rgb_color(t_rgb_color color)
{
	printf("(%d:%d:%d)", color.red, color.green, color.blue);
}
