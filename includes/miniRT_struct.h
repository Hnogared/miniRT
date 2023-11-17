/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:41:32 by motoko            #+#    #+#             */
/*   Updated: 2023/11/17 15:51:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

/*
 * Vector structure holding its amplitudes in the x, y and z axes.
 *
 * float x	-> amplitude in the x axis
 * float y	-> amplitude in the y axis
 * float z	-> amplitude in the z axis
 */
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

/*
 * Coordinates structure holding x, y and z coordinates.
 *
 * float x	-> x coordinate
 * float y	-> y coordinate
 * float z	-> z coordinate
 */
typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
}				t_coords;

/*
 * Ray data structure used for the ray tracing.
 *
 * t_vector vector			-> direction towards which the ray is going in vector form
 * t_coords coords			-> current coordinates of the ray point
 * t_coords origin_coords	-> the coordinates from which the ray originated
 */
typedef struct s_ray
{
	t_vector	vector;
	t_coords	coords;
	t_coords	origin_coords;
}				t_ray;

/*
 * Color structure holding its red, green and blue values.
 *
 * unsignd char red		-> the red value of the color (in range: 0-255)
 * unsignd char green	-> the green value of the color (in range: 0-255)
 * unsignd char blue	-> the blue value of the color (in range: 0-255)
 */
typedef struct s_rgb_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}				t_rgb_color;

/*
 * Ambient lighting data structure.
 *
 * float ratio			-> ratio/strength of the ambient lighting (0.0-1.0)
 * t_rbg_color color	-> color of the ambient lighting in rgb (0-255:0-255:0-255)
 */
typedef struct s_ambient_light
{
	float		ratio;
	t_rgb_color	color;
}				t_ambient_light;

/*
 * Camera special data structure used to complement the t_object structure.
 *
 * int fov	-> FOV of the camera (0-180)
 */
typedef struct s_camera
{
	int			fov;
}				t_camera;

/*
 * Light special data structure used to complement the t_object structure.
 *
 * float brightness	-> brightness ratio of the light (0.0-1.0)
 */
typedef struct s_light
{
	float		brightness;
}				t_light;

/*
 * Sphere special data structure used to complement the t_object structure.
 *
 * float diameter		-> diameter of the sphere
 * float radius			-> radius of the sphere
 * t_rgb_color color	-> color of the sphere in rgb (0-255:0-255:0-255)
 */
typedef struct s_sphere
{
	float		diameter;
	float		radius;
	t_rgb_color	color;
}				t_sphere;

/*
 * Plane special data structure used to complement the t_object structure.
 *
 * t_rgb_color color	-> color of the plane in rgb (0-255:0-255:0-255)
 */
typedef struct s_plane
{
	t_rgb_color	color;
}				t_plane;

/*
 * Cylinder special data structure used to complement the t_object structure.
 *
 * float diameter		-> diameter of the cylinder
 * float height			-> height of the cylinder
 * t_rgb_color color	-> color of the cylinder in rgb (0-255:0-255:0-255)
 */
typedef struct s_cylinder
{
	float		diameter;
	float		height;
	t_rgb_color	color;
}				t_cylinder;

/*
 * Union holding either a camera, light, sphere, plane or cylinder special data.
 * This does not contain the object's position/orientation.
 *
 * t_camera camera		-> camera data		{fov}
 * t_light light		-> light data		{brightness}
 * t_sphere sphere		-> sphere data		{diameter, radius, color}
 * t_plane plane		-> plane data		{color}
 * t_cylinder cylinder	-> cylinder data	{diameter, height, color}
 */
typedef union u_special_data
{
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_special_data;

/*
 * Structure holding an object's data, as well as its function to display its
 * special data (camera / light / sphere / plane / cylinder).
 *
 * unsigned short type			-> object type [ex: SPHERE_OBJ] (see miniRT_macro.h)
 * bool has_color				-> boolean true if the object has a color property
 * t_coords coords				-> coordinates structure of the object
 * t_vector orientation_vector	-> normal vector structure to rotate the object
 * t_special_data special_data	-> additional special data (camera/light/... data)
 * void (*data_print_func)		-> pointer to the special data display function
 */
typedef struct s_object
{
	unsigned short	type;
	bool			has_color;
	t_coords		coords;
	t_vector		orientation_vector;
	t_special_data	special_data;
	void			(*data_print_func)(t_special_data special_data);
}				t_object;

/* Image data structure.
 *
 * int width			-> width of the image
 * int height			-> height of the image
 * int bits_per_pixel	-> amount of bits stored for a single pixel's color
 * int line_size		-> length of one of the image's pixel lines (in bytes)
 * int endian			-> system endian for pixel color reading/writing
 * void *ptr			-> pointer to the image's memory block
 * char *addr			-> pointer to the image's first pixel in its memory
 */
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

/*
 * Structure holding a window and its image's data.
 *
 * int width		-> the window's width
 * int height		-> the window's height
 * t_image image	-> the window's own image structure
 * void *ptr		-> pointer to the window memory block
 */
typedef struct s_window
{
	int		width;
	int		height;
	t_image	image;
	void	*ptr;
}				t_window;

/*
 * Structure holding all the program's data.
 *
 * int pixel_ratio			-> number of pixels used to display one pixel
 * t_window main_window		-> the main window structure to display on the screen
 * t_ambient_light ambient_l-> the scene's ambient lighting data structure
 * t_object *scene_objects	-> pointer to all the scene's objects {plane,light...}
 * void *mlx_ptr			-> pointer to the mlx instance memory block
 */
typedef struct s_data
{
	int				pixel_ratio;
	t_window		main_window;
	t_ambient_light	ambient_l;
	t_object		*scene_objects;
	t_xvar			*mlx_ptr;
	int				test;
}				t_data;

#endif
