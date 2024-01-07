/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:18:03 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 22:20:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

/* get_object_color.c */
t_rgb_color	get_uncolored_color(
				__attribute__((unused)) t_special_data special_data);
t_rgb_color	get_sphere_color(t_special_data special_data);
t_rgb_color	get_plane_color(t_special_data special_data);
t_rgb_color	get_cylinder_color(t_special_data special_data);
t_rgb_color	get_light_color(t_special_data special_data);

/* object_creation.c */
t_object	*new_camera(t_object *to_set, t_coords coords, int fov);
t_object	*new_light(t_object *to_set, t_coords coords, float brightness);
t_object	*new_sphere(t_object *to_set, t_coords coords, float diameter);
t_object	*new_plane(t_object *to_set, t_coords coords);
t_object	*new_cylinder(t_object *to_set, t_coords coords, float diameter,
				float height);

/* object_interaction.c */
t_object	*get_object_ptr(unsigned short type, t_object *objects_list,
				int list_size);

/* object_modification.c */
t_object	*set_object_coords(t_object *to_set, t_coords coords);
t_object	*set_object_orientation(t_object *to_set, t_vector orient_vector);
t_object	*rotate_object(t_object *to_rotate, float angle, t_vector axis);
t_object	*set_object_color(t_object *to_set, t_rgb_color color);

/* print_object_data.c */
void		print_object_data(t_object object);
void		print_coords(t_coords coords, char *name);
void		print_vector(t_vector vector, char *name);
void		print_rgb_color(t_rgb_color color, char *name);
void		print_basis(t_basis basis, char *name);

/* print_object_data_2.c */
void		print_camera_data(t_special_data special_data);
void		print_sphere_data(t_special_data special_data);
void		print_light_data(t_special_data special_data);
void		print_plane_data(t_special_data special_data);
void		print_cylinder_data(t_special_data special_data);

#endif
