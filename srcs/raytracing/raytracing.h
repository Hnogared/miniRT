/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:09:37 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 22:01:24 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

/* ************************************************************************** */
/* raytrace.c                                                                 */
/* ************************************************************************** */
/*
 * Function to trace the parameter ray and return the color resulting of its
 * bounces.
 * If the anti aliasing boolean is set to true, sends 4 diagonally spread out
 * rays from the parameter ray and returns their average.
 *
 * @param const t_data *data	-> pointer to the data to use for tracing
 * @param t_ray ray				-> the ray to trace
 * @param bool anti_aliasing	-> enables anti aliasing if true
 * @return size_t				-> the calculated ray color
 *
 * @child_func diffused_raytracing	-> function to average out multiple rays
 */
size_t		raytrace(const t_data *data, t_ray ray, bool anti_aliasing);

/* ************************************************************************** */
/* set_view_rays.c                                                            */
/* ************************************************************************** */
/*
 * Function to return a zero initialized t_ray structure with given vector and
 * origin coords.
 *
 * @param t_vector vector			-> orientation vector of the ray
 * @param t_coords origin_coords	-> coordinates from which the ray starts
 * @return t_ray					-> the newly initialized t_ray structure
 */
t_ray		new_ray(t_basis basis, t_coords origin_coords);

/*
 * Function to allocate, if needed (@param bool needs_alloc), and fill a
 * pointed t_ray double pointer with t_ray structures which vectors are
 * calculated from the @param t_window window and @param t_object camera data.
 * The window is used for the size of the double pointer (1 ray / virtual pixel)
 * and the camera's FOV is used to calculate the orientation of each ray.
 * The calculated rays are ready to be traced.
 * If the parameter rays tab is already allocated and the allocation boolean is
 * true, the rays tab gets reallocated.
 *
 * @param t_ray ***rays_tab	-> pointer to the t_ray double pointer to alloc/fill
 * @param t_window window	-> window for which to generate the rays
 * @param t_object camera	-> camera through which to generate the rays
 * @param bool needs_alloc	-> true if @param t_ray ***rays_tab needs allocation 
 * @return int				-> status code [success/err/alloc_err]
 *
 * @child_func alloc_rays_tab	-> function to allocate the rays double pointer
 * @child_func set_rays_tab		-> function to fill the rays double pointer
 */
int			set_view_rays(t_ray ***rays_tab, t_window window, t_object camera,
				bool needs_alloc);

/*
 * Function to setup the view rays using the parameter data active camera and
 * render window.
 * If the parameter boolean is true, allocates the view rays if they haven't been
 * yet or reallocates them if already allocated.
 * Displays an error, frees up the data and exits if the function set_view_rays
 * failed (which would very likely mean an allocation issue).
 *
 * @param t_data *data		-> pointer to the data for the rays generation
 * @param bool needs_alloc	-> true if allocation/reallocation is needed
 */
void		get_render_view_rays(t_data *data, bool needs_alloc);

/* ************************************************************************** */
/* shadow_ray.c                                                               */
/* ************************************************************************** */
/*
 * Function to get the lighting color of a point at the parameter coords
 * according to the lights present in the parameter objects array.
 *
 * @param t_coords start_coords			-> coords of the point in space to check
 * @param t_object *objects_array		-> pointer to the scene objects to check
 * @param unsigned short objects_count	-> amount of scene objects to check
 * @param t_ambient_light ambient_l		-> the scene ambient lighting
 * @return t_rgb_color					-> the resulting lighting color
 *
 * @child_func advance_shadow_ray	-> function to check if a ray touches a light
 */
t_rgb_color	shadow_ray(t_coords start_coords, const t_object *objects_array,
				unsigned short objects_count, t_ambient_light ambient_l);

#endif
