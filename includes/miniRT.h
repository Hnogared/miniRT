/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 14:06:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define SYNTAX_ERROR 2

# define BLANK_OBJ		0
# define CAMERA_OBJ		1
# define LIGHT_OBJ		2
# define SPHERE_OBJ		3
# define PLANE_OBJ		4
# define CYLINDER_OBJ	5

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
}				t_coords;

typedef struct s_rgb_color
{
	int	red;
	int	green;
	int	blue;
}				t_rgb_color;

typedef struct s_ambient_lighting
{
	int			ratio;
	t_rgb_color	color;
}				t_ambient_lighting;

typedef struct s_camera
{
	int			fov;
}				t_camera;

typedef struct s_light
{
	int			brightness;
}				t_light;

typedef struct s_sphere
{
	float		diameter;
	float		radius;
	t_rgb_color	color;
}				t_sphere;

typedef struct s_plane
{
	t_rgb_color	color;
}				t_plane;

typedef struct s_cylinder
{
	float		diameter;
	float		height;
	t_rgb_color	color;
}				t_cylinder;

typedef union
{
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
} t_special_data;

typedef struct s_object
{
	unsigned short	type;
	t_coords		coords;
	t_vector		orientation_vector;
	t_special_data	special_data;
	void			(*data_print_func)(t_special_data special_data);
}				t_object;

/*
typedef struct s_object
{
	unsigned short	type;
	t_coords		coords;
	t_vector		orientation_vector;
	//t_print_func	data_print_func;
	union
	{
		t_camera	camera_data;
		t_light		light_data;
		t_sphere	sphere_data;
		t_plane		plane_data;
		t_cylinder	cylinder_data;
	};
	//t_special_data	special_data;
}				t_object;
*/

typedef struct s_data
{
	t_object	*scene_objects;
}				t_data;

int	check_file(char *scene);

/* Srcs/debug */
/* print_object_data.c */
void	print_object_data(t_object object);
void	print_coords(t_coords coords);
void	print_vector(t_vector vector);
void	print_rgb_color(t_rgb_color color);

/* print_object_data_2.c */
/*
void	print_camera_data(t_camera camera);
void	print_sphere_data(t_sphere sphere);
void	print_light_data(t_light light);
void	print_plane_data(t_plane plane);
void	print_cylinder_data(t_cylinder cylinder);
*/

void	print_camera_data(t_special_data camera);
void	print_sphere_data(t_special_data sphere);
void	print_light_data(t_special_data light);
void	print_plane_data(t_special_data plane);
void	print_cylinder_data(t_special_data cylinder);

#endif
