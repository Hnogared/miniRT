/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object_data_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:37:20 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/04 15:40:30 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to display a camera special data in the terminal.
 * Make sure to give as parameter a special data union that has been modified as
 * a camera special data, else you will get undefined data displayed.
 *
 * t_special_data special_data	-> the camera formatted special_data to display
 */
void	print_camera_data(t_special_data special_data)
{
	ft_printf("[Camera data]\n");
	ft_printf("Fov : %d\n", special_data.camera.fov);
}

/*
 * Function to display a light special data in the terminal.
 * Make sure to give as parameter a special data union that has been modified as
 * a light special data, else you will get undefined data displayed.
 *
 * t_special_data special_data	-> the light formatted special_data to display
 */
void	print_light_data(t_special_data special_data)
{
	ft_printf("[Light data]\n");
	ft_printf("Brightness : %f\n", special_data.light.brightness);
}

/*
 * Function to display a sphere special data in the terminal.
 * Make sure to give as parameter a special data union that has been modified as
 * a sphere special data, else you will get undefined data displayed.
 *
 * t_special_data special_data	-> the sphere formatted special_data to display
 */
void	print_sphere_data(t_special_data special_data)
{
	ft_printf("[Sphere data]\n");
	ft_printf("Diameter : %f\n", special_data.sphere.diameter);
	ft_printf("Radius : %f\n", special_data.sphere.radius);
	ft_printf("Color : ");
	print_rgb_color(special_data.sphere.color);
}

/*
 * Function to display a plane special data in the terminal.
 * Make sure to give as parameter a special data union that has been modified as
 * a plane special data, else you will get undefined data displayed.
 *
 * t_special_data special_data	-> the plane formatted special_data to display
 */
void	print_plane_data(t_special_data special_data)
{
	ft_printf("[Plane data]\n");
	ft_printf("Color : ");
	print_rgb_color(special_data.plane.color);
}

/*
 * Function to display a cylinder special data in the terminal.
 * Make sure to give as parameter a special data union that has been modified as
 * a cylinder special data, else you will get undefined data displayed.
 *
 * t_special_data special_data	-> the cylinder formatted special_data to display
 */
void	print_cylinder_data(t_special_data special_data)
{
	ft_printf("[Cylinder data]\n");
	ft_printf("Diameter : %f\n", special_data.cylinder.diameter);
	ft_printf("Height : %f\n", special_data.cylinder.height);
	ft_printf("Color : ");
	print_rgb_color(special_data.cylinder.color);
}
