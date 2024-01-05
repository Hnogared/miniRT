/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 11:51:22 by hnogared         ###   ########.fr       */
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

# include "miniRT_macro.h"
# include "miniRT_struct.h"
# include "miniRT_error.h"


void	get_main_view_rays(t_data *data, bool needs_alloc);

/* SRCS/BASIS */
/* orthonormal_basis.c */
t_basis	get_ortho_basis_from_x(t_vector xxx_orientation);
t_basis	get_ortho_basis_from_y(t_vector y_orientation);
t_basis	get_ortho_basis_from_z(t_vector z_orientation);

/* switch_basis.c */
t_ray			switch_ray_basis(t_ray to_rotate, t_basis new_basis,
					t_basis old_basis);
t_coords		switch_coords_basis(t_coords to_rotate, t_basis new_basis,
					t_basis old_basis);
t_vector	switch_vector_basis(t_vector to_rotate, t_basis new_basis,
					t_basis old_basis);

/* SRCS/VECTOR */
/* rotation.c */
float			to_rad(float degree_angle);
t_basis			axial_basis_rotation(t_basis to_rotate, float angle,
					t_vector axis);
t_vector		axial_vector_rotation(t_vector to_rotate, float angle,
					t_vector axis);
t_vector		matrix_vector_rotation(t_vector to_rotate,
					float rot_matrix[3][3]);
t_coords		matrix_coords_rotation(t_coords to_rotate,
					float rot_matrix[3][3]);
void			get_rotation_matrix(float rot_matrix_to_set[3][3],
					t_vector vector1, t_vector vector2);

/* SRCS/PARSING */
int				check_file(char *scene);
char			*get_file(const t_data *data, const char *scene);
int				check_scene(t_data *data, char **tab);
int				check_numbers(char ***block);
int				check_num_objects(char ***block);
int				check_range_numbers(char ***block);
int				check_range_fov(char *fov);
int				check_range_vectors(char *str);
int				check_range_color(char *str);
int				check_range_light(char *str);
void			check_char(char ***block);
void			check_num_args(char ***block);
void			free_parsing_and_exit(t_data *data, char ***block);
void			free_block(char ***block);

/* initialize data */
int				initialize_object(t_data *data, char **tab);
int				initialize_mlx(t_data *data);
void			obj_a(t_data *data, char *s);
void			obj_c(unsigned int index, t_data *data, char *s, int *pos);
void			obj_l(unsigned int index, t_data *data, char *s, int *pos);
void			obj_pl(unsigned int index, t_data *data, char *s, int *pos);
void			obj_sp(unsigned int index, t_data *data, char *s, int *pos);
void			obj_cy(unsigned int index, t_data *data, char *s, int *pos);

/* free_and_exit.c */
noreturn int	free_and_exit(t_data *data);
void			free_data(t_data *data);
void			free_str_tab(char **str_tab);

/* SRCS/OBJECT_MANAGEMENT */
/* get_object_color.c */
t_rgb_color		get_uncolored_color(__attribute__((unused))
					t_special_data special_data);
t_rgb_color		get_sphere_color(t_special_data special_data);
t_rgb_color		get_plane_color(t_special_data special_data);
t_rgb_color		get_cylinder_color(t_special_data special_data);
t_rgb_color		get_light_color(t_special_data special_data);

/* object_creation.c */
t_object		*new_camera(t_object *to_set, t_coords coords, int fov);
t_object		*new_light(t_object *to_set, t_coords coords, float brightness);
t_object		*new_sphere(t_object *to_set, t_coords coords, float diameter);
t_object		*new_plane(t_object *to_set, t_coords coords);
t_object		*new_cylinder(t_object *to_set, t_coords coords, float diameter,
					float height);

/* object_interaction.c */
t_object		*get_object_ptr(unsigned short type, t_object *objects_list,
					int list_size);

/* object_modification.c */
t_object		*set_object_coords(t_object *to_set, t_coords coords);
t_object		*set_object_orientation(t_object *to_set,
					t_vector orient_vector);
t_object		*rotate_object(t_object *to_rotate, float angle, t_vector axis);
t_object		*set_object_color(t_object *to_set, t_rgb_color color);

/* print_object_data.c */
void			print_object_data(t_object object);
void			print_coords(t_coords coords, char *name);
void			print_vector(t_vector vector, char *name);
void			print_rgb_color(t_rgb_color color, char *name);
void			print_basis(t_basis basis, char *name);

/* print_object_data_2.c */
void			print_camera_data(t_special_data special_data);
void			print_sphere_data(t_special_data special_data);
void			print_light_data(t_special_data special_data);
void			print_plane_data(t_special_data special_data);
void			print_cylinder_data(t_special_data special_data);

/* Theouche*/
char			*conv(t_rgb_color color);
t_vector		sous_vec_coord(t_coords a, t_coords b);
t_vector		add_vec_coord(t_coords a, t_coords b);
t_vector		sous_vec_vec(t_vector a, t_vector b);
t_vector		add_vec_vec(t_vector a, t_vector b);
t_coords		add_vec_coord_vec(t_coords a, t_vector b);
t_vector		prod_vec_int(t_vector a, int k);
t_vector		prod_vec_float(t_vector a, float k);
float			prod_scal_vec(t_vector a, t_vector b);
t_vector		prod_vec_vec(t_vector a, t_vector b);
t_vector		calc_ref_form(t_vector i, t_vector n);
float			magnitude(t_vector n);
t_vector		normalise(t_vector n);
float			dist(t_coords a, t_coords b);
t_coords		advance_on_vec(t_coords dep, t_vector dir, int k);
t_coords		find_pos_touch(t_ray *ray, float t);
t_coords		give_coord(t_coords coord);
float			good_sol(float delta, float b, float a);
float			prod_scal_coord(t_coords a, t_coords b);
float			prod_scal_vec_coord(t_vector a, t_coords b);
float			magnitude_coord(t_coords n);
void			try_sphere(t_ray *ray, t_object obj, int i);
void			try_plan(t_ray *ray, t_object plan, int i);
void			try_plan_cyl(t_ray *ray, t_coords cp, t_vector n, t_object obj,
					int i);
void			try_cylinder_ext(t_ray *ray, t_object obj, int i);
void			try_cylinder_side(t_ray *ray, t_object obj, int i);
void			try_light(t_ray *ray, t_object l, int i);
t_vector		cal_sphere(t_ray *ray, t_object sphere);
t_vector		cal_plan(t_ray *ray, t_object plan);
t_vector		cal_cylinder_ext(t_ray *ray, t_object cylindre, int res);
t_vector		cal_cylinder_side(t_ray *ray, t_object cylindre);
t_vector		calcul_ref(t_ray *ray, t_object obj, int res);
void			ray_advance(const t_data *data, t_ray *ray);
void			print_vec(t_vector vec);
void			print_coord(t_coords cor);
t_coords		advance_on_vec_z_sup(t_coords dep, t_vector dir, int k);
t_coords		advance_on_vec_z_inf(t_coords dep, t_vector dir, int k);
t_coords		advance_on_vec_z(t_coords dep, t_coords touch);
float			to_rad(float degree_angle);
t_vector		prod_vec_float(t_vector a, float k);
int 			test(t_ray aligned_ray, t_object obj);
void			give_sol(t_ray	*aligned_ray, float	t, int i);
t_ray			switch_rb(t_ray *ray, t_object obj);
t_coords		switch_cb(t_object obj);

/* SRCS/DISPLAY */
/* image_handling.c */
t_image			my_new_image(void *mlx_ptr, int width, int height);
size_t			get_image_pixel(t_image image, int x, int y);
void			set_image_pixel(t_image *image, int x, int y, size_t color);

/* render_window.c */
int				open_render_window(t_data *data, char *title);
int				redraw_render_window(t_data *data);

/* rgb_color.c */
int				ft_min(int num1, int num2);
size_t			rgb_to_sizet(t_rgb_color color);
size_t			sizet_color_mix(size_t color1, size_t color2, float ratio);
t_rgb_color		rgb_color_lighten(t_rgb_color start_color,
					t_rgb_color add_color, float ratio);
t_rgb_color		rgb_color_mix(t_rgb_color start_color, t_rgb_color mix_color,
					float ratio);

/* window_handling.c */
size_t			get_window_pixel(t_window window, int x, int y);
size_t			get_window_virtual_pixel(t_window window, int x, int y);
t_window		my_new_window(void *mlx_ptr, int dimensions[2], int pixel_ratio,
					char *title);
void			my_destroy_window(void *mlx_ptr, t_window *window);
void			redraw_window(void *mlx_ptr, t_window *window);

/* window_modification.c */
t_window		*set_window_pixel_ratio(t_window *to_modify, int pixel_ratio);
void			set_window_pixel(t_window *window, int x, int y, size_t color);
void			set_window_virtual_pixel(t_window *window, int x, int y,
					size_t color);
void			put_square_to_window(t_window *window, int start_coords[2],
					int size[2], size_t color);
void			put_percent_to_window(t_xvar *mlx_ptr, t_window window,
					int percentage, int color);

/* SRCS/RAYTRACING */
/* get_view_rays.c */
t_ray			new_ray(t_basis basis, t_coords origin_coords);
int				set_view_rays(t_ray ***rays_tab, t_window window,
					t_object camera, bool needs_alloc);

/* raytrace.c */
size_t			test_grid(__attribute__((unused)) const t_data *data, int x,
					int y);
size_t			raytrace(const t_data *data, t_ray ray, bool anti_aliasing);

/* shadow_ray.c */
t_rgb_color		shadow_ray(t_coords start_coords, const t_object *objects_array,
					unsigned short objects_count, t_ambient_light ambient_l);

/* SRCS/USER_INTERFACE */
/* keyboard.c */
int				key_press_handler(int keycode, t_data *data);
int				key_release_handler(int keycode, t_data *data);

/* SRCS/VECTOR */
/* vect.c */
int				do_touch(t_ray *ray, t_object obj, int i);

#endif
