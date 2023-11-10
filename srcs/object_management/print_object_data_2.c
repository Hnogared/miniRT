/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object_data_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:37:20 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 17:23:49 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_camera_data(t_special_data special_data)
{
	printf("[Camera data]\n");
	printf("Fov : %d\n", special_data.camera.fov);
}

void	print_light_data(t_special_data special_data)
{
	printf("[Light data]\n");
	printf("Brightness : %d\n", special_data.light.brightness);
}

void	print_sphere_data(t_special_data special_data)
{
	printf("[Sphere data]\n");
	printf("Diameter : %f\n", special_data.sphere.diameter);
	printf("Radius : %f\n", special_data.sphere.radius);
	printf("Color : ");
	print_rgb_color(special_data.sphere.color);
	printf("\n");
}

void	print_plane_data(t_special_data special_data)
{
	printf("[Plane data]\n");
	printf("Color : ");
	print_rgb_color(special_data.plane.color);
}

void	print_cylinder_data(t_special_data special_data)
{
	printf("[Cylinder data]\n");
	printf("Diameter : %f\n", special_data.cylinder.diameter);
	printf("Height : %f\n", special_data.cylinder.height);
	printf("Color : ");
	print_rgb_color(special_data.cylinder.color);
}
