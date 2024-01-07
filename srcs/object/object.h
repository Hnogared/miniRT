/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:18:03 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 22:15:41 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

/* ************************************************************************** */
/* get_object_color.c                                                         */
/* ************************************************************************** */
/*
 * Function to return the color of an object with no color attribute.
 *
 * @param[unused] t_special_data special_data	-> placeholder special data 
 * @return t_rgb_color							-> the default color structure
 */
t_rgb_color	get_uncolored_color(
				__attribute__((unused)) t_special_data special_data);

/*
 * Function to return the color of a sphere's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different object.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_sphere_color(t_special_data special_data);

/*
 * Function to return the color of a plane's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different object.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_plane_color(t_special_data special_data);

/*
 * Function to return the color of a cylinder's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different object.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_cylinder_color(t_special_data special_data);

/*
 * Function to return the color of a light's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different object.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_light_color(t_special_data special_data);

/* ************************************************************************** */
/* object_creation.c                                                          */
/* ************************************************************************** */
/*
 * Function to initialize a camera object.
 * The camera will be initialized to zero except for its coords and fov.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the camera's coords to set
 * @param int fov			-> the camera's fov to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_camera(t_object *to_set, t_coords coords, int fov);

/*
 * Function to initialize a light object.
 * The light will be initialized to zero except for its coords and brightness.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the light's coords to set
 * @param int brightness	-> the light's brightness to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_light(t_object *to_set, t_coords coords, float brightness);

/*
 * Function to initialize a sphere object.
 * The sphere will be initialized to zero except for its coords, diameter and
 * radius, which is calculated from the parameter diameter.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the sphere's coords to set
 * @param float diameter	-> the sphere's diameter to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_sphere(t_object *to_set, t_coords coords, float diameter);

/*
 * Function to initialize a plane object.
 * The plane will be initialized to zero except for its coords.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the plane's coords to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_plane(t_object *to_set, t_coords coords);

/*
 * Function to initialize a cylinder object.
 * The cylinder will be initialized to zero except for its coords, diameter and
 * height.
 *
 * @param t_object *to_set	-> pointer to the object structure to modify
 * @param t_coords coords	-> the cylinder's coords to set
 * @param float diameter	-> the cylinder's diameter to set
 * @param float height		-> the cylinder's height to set
 * @return t_object *		-> pointer to the newly initialized object structure
 */
t_object	*new_cylinder(t_object *to_set, t_coords coords, float diameter,
				float height);

/* ************************************************************************** */
/* object_data_display.c                                                      */
/* ************************************************************************** */
/*
 * Function to display a t_object object structure's data in the terminal.
 * The object's data_print_func pointer is needed to display its special data.
 *
 * @param t_object object	-> the object structure to display
 */
void		print_object_data(t_object object);

/*
 * Function to display a t_coords coordinates structure in the terminal.
 *
 * @param t_coords coords	-> coordinates structure to display
 * @param const char *name	-> name of the coordinates displayed
 */
void		print_coords(t_coords coords, const char *name);

/*
 * Function to display a t_vector vector structure in the terminal.
 *
 * @param t_vector vector	-> vector structure to display
 * @param const char *name	-> name of the vector displayed
 */
void		print_vector(t_vector vector, const char *name);

/*
 * Function to display a t_rgb_color color structure in the terminal.
 *
 * @param t_rgb_color color	-> rgb color structure to display
 * @param const char *name	-> name of the color displayed
 */
void		print_rgb_color(t_rgb_color color, const char *name);

/*
 * Function to display a t_basis basis structure in the terminal.
 *
 * @param t_basis basis		-> basis structure to display
 * @param const char *name	-> name of the basis displayed
 */
void		print_basis(t_basis basis, const char *name);

/* ************************************************************************** */
/* object_data_display_2.c                                                    */
/* ************************************************************************** */
/*
 * Function to display a camera special data in the terminal.
 * Prints undefined data if the parameter special data has been modified as a
 * different type of object.
 *
 * t_special_data special_data	-> the camera formatted special_data to display
 */
void		print_camera_data(t_special_data special_data);

/*
 * Function to display a light special data in the terminal.
 * Prints undefined data if the parameter special data has been modified as a
 * different type of object.
 *
 * t_special_data special_data	-> the light formatted special_data to display
 */
void		print_light_data(t_special_data special_data);

/*
 * Function to display a sphere special data in the terminal.
 * Prints undefined data if the parameter special data has been modified as a
 * different type of object.
 *
 * t_special_data special_data	-> the sphere formatted special_data to display
 */
void		print_sphere_data(t_special_data special_data);

/*
 * Function to display a plane special data in the terminal.
 * Prints undefined data if the parameter special data has been modified as a
 * different type of object.
 *
 * t_special_data special_data	-> the plane formatted special_data to display
 */
void		print_plane_data(t_special_data special_data);

/*
 * Function to display a cylinder special data in the terminal.
 * Prints undefined data if the parameter special data has been modified as a
 * different type of object.
 *
 * t_special_data special_data	-> the cylinder formatted special_data to display
 */
void		print_cylinder_data(t_special_data special_data);

/* ************************************************************************** */
/* object_interaction.c                                                       */
/* ************************************************************************** */
/*
 * Function to retrieve the pointer to the first t_object structure of the given
 * type in an array of objects.
 *
 * @param unsigned short type			-> type of the object to look for
 * @param const t_object *objects_list	-> array of objects 
 */
t_object	*get_object_ptr(unsigned short type, const t_object *objects_list,
				int list_size);

/* ************************************************************************** */
/* object_modification.c                                                      */
/* ************************************************************************** */
/*
 * Function to set the coordinates of an object to a given set.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_coords new_coords	-> the new coordinates' structure
 * @[rednudant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*set_object_coords(t_object *to_set, t_coords coords);

/*
 * Function to change the orientation vector, and therefore the local basis, of
 * an object.
 * A camera's orientation vector is the x axis of its local basis while the
 * other objects use their local basis' z axis.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_vector *new_vector	-> the new vector's structure
 * @[redundant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*set_object_orientation(t_object *to_set, t_vector orient_vector);

/*
 * Function to rotate an object around an axis at a given angle.
 * A camera's orientation vector is the x axis of its local basis while the
 * other objects use their local basis' z axis.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_rotate	-> pointer to the object to rotate
 * @param float angle			-> angle of the rotation to apply
 * @param t_vector axis			-> axis along which to rotate the object
 * @[redundant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*rotate_object(t_object *to_rotate, float angle, t_vector axis);

/*
 * Function to change the color of an object to a given rgb set.
 * The pointed parameter object is directly modified in the function, the
 * returned pointer is for redundancy.
 *
 * @param t_object *to_set		-> pointer to the object structure to modify
 * @param t_rgb_color new_color	-> the new color's structure
 * @[redundant]return t_object *-> pointer to the newly modified object structure
 */
t_object	*set_object_color(t_object *to_set, t_rgb_color color);

#endif
