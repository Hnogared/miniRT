/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:41:32 by motoko            #+#    #+#             */
/*   Updated: 2023/11/16 17:50:54 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define	MINIRT_STRUCT_H

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

typedef struct s_ray
{
	t_vector	vector;
	t_coords	coords;
}				t_ray;

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
	int			test;
}				t_data;
#endif
