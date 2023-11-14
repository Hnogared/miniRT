/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/13 21:22:21 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# include "miniRT_macro.h"

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
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
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
	bool			has_color;
	t_coords		coords;
	t_vector		orientation_vector;
	t_special_data	special_data;
	void			(*data_print_func)(t_special_data special_data);
}				t_object;

typedef struct s_image
{
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	void	*ptr;
	char	*addr;
}				t_image;

typedef struct s_window
{
	int		width;
	int		height;
	t_image	image;
	void	*ptr;
}				t_window;

typedef struct s_data
{
	t_window	main_window;
	t_object	*scene_objects;
	void		*mlx_ptr;
}				t_data;

int		check_file(char *scene);
char	*get_file(char *scene);
char	***check_scene(char **tab);
void	check_char(char ***block);
void	check_numbers(char ***block);
void	check_range_numbers(char ***block);
void	err(char *str);

/* SRCS/OBJECT_MANAGEMENT */
/* object_creation.c */
t_object	*new_camera(t_object *to_set, t_coords coords, int fov);
t_object	*new_light(t_object *to_set, t_coords coords, int brightness);
t_object	*new_sphere(t_object *to_set, t_coords coords, float diameter);
t_object	*new_plane(t_object *to_set, t_coords coords);
t_object	*new_cylinder(t_object *to_set, t_coords coords, float diameter,
	float height);

/* object_modification.c */
t_object	*set_object_coords(t_object *to_set, t_coords coords);
t_object	*set_object_orientation(t_object *to_set, t_vector orient_vector);
t_object	*set_object_color(t_object *to_set, t_rgb_color color);

/* print_object_data.c */
void		print_object_data(t_object object);
void		print_coords(t_coords coords);
void		print_vector(t_vector vector);
void		print_rgb_color(t_rgb_color color);

/* print_object_data_2.c */
void		print_camera_data(t_special_data camera);
void		print_sphere_data(t_special_data sphere);
void		print_light_data(t_special_data light);
void		print_plane_data(t_special_data plane);
void		print_cylinder_data(t_special_data cylinder);

/* Theouche*/
char    *conv(t_rgb_color color);

/* SRCS/DISPLAY */
/* image_management.c */
t_image		*my_new_image(void *mlx_ptr, t_image *new_img_p, int width,
	int height);
void		my_put_pixel_to_image(t_image *image, int x, int y, int color);

/* window_management.c */
int			open_main_window(t_data *data, char *title);
t_window	*my_new_window(void *mlx_ptr, t_window *new_window_p,
	int dimensions[2], char *title);
void		my_destroy_window(void *mlx_ptr, t_window *window);
void		my_put_pixel_to_window(t_window *window, int x, int y, int color);
void		redraw_window(void *mlx_ptr, t_window *window);

#endif
