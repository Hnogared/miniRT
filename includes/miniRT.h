/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/18 16:23:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdnoreturn.h>
# include <math.h>
# include <X11/Xlib.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# include "miniRT_struct.h"
# include "miniRT_macro.h"
# include "miniRT_error.h"

int				check_file(char *scene);
char			*get_file(char *scene);
void			check_scene(char **tab);
void			check_char(char ***block);
void			check_numbers(char ***block);
int				check_range_numbers(char ***block);
void			err(char *str);
void			check_num_args(char ***block);
void			check_num_objects(char ***block);
int				check_range_fov(char *fov);
int				check_range_vectors(char *str);
int				check_range_color(char *str);
int				check_range_light(char *str);

/* free_and_exit.c */
noreturn int	free_and_exit(t_data *data);
void			free_data(t_data *data);
void			free_str_tab(char **str_tab);

/* SRCS/OBJECT_MANAGEMENT */
/* object_creation.c */
t_object		*new_camera(t_object *to_set, t_coords coords, int fov);
t_object		*new_light(t_object *to_set, t_coords coords, int brightness);
t_object		*new_sphere(t_object *to_set, t_coords coords, float diameter);
t_object		*new_plane(t_object *to_set, t_coords coords);
t_object		*new_cylinder(t_object *to_set, t_coords coords, float diameter,
					float height);

/* object_modification.c */
t_object		*set_object_coords(t_object *to_set, t_coords coords);
t_object		*set_object_orientation(t_object *to_set,
					t_vector orient_vector);
t_object		*set_object_color(t_object *to_set, t_rgb_color color);

/* print_object_data.c */
void			print_object_data(t_object object);
void			print_coords(t_coords coords);
void			print_vector(t_vector vector);
void			print_rgb_color(t_rgb_color color);

/* print_object_data_2.c */
void			print_camera_data(t_special_data camera);
void			print_sphere_data(t_special_data sphere);
void			print_light_data(t_special_data light);
void			print_plane_data(t_special_data plane);
void			print_cylinder_data(t_special_data cylinder);

/* Theouche*/
char			*conv(t_rgb_color color);

/* SRCS/DISPLAY */
/* image_management.c */
t_image			my_new_image(void *mlx_ptr, int width, int height);
size_t			get_image_pixel(t_image image, int x, int y);
void			my_put_pixel_to_image(t_image *image, int x, int y,
					size_t color);

/* main_window.c */
int				open_main_window(t_data *data, char *title);
void			redraw_main_window(t_data *data);

/* window_management.c */
t_window		my_new_window(void *mlx_ptr, int dimensions[2], char *title);
void			my_destroy_window(void *mlx_ptr, t_window *window);
void			my_put_pixel_to_window(t_window *window, int x, int y,
					size_t color);
void			my_put_square_to_window(t_window *window, int start_coords[2],
					int size[2], size_t color);
void			redraw_window(void *mlx_ptr, t_window *window);

/* SRCS_USER_INTERFACE */
/* keyboard.c */
int				key_handler(int keycode, t_data *data);
void			init_key_hooks(t_data *data);

#endif
