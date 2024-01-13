/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:35:57 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/09 00:10:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*pour cylinder side*/
//1ere etape, trouver le C', sachant que CP^2 = CC'^2 + r^2
//donc CC' = CP^2 - r^2
// et C' = C + CC'*N;

/*
 * Function to calculate the vector resulting from the reflection of a ray on a
 * sphere object.
 *
 * @param t_ray ray			-> the ray to reflect
 * @param t_object sphere	-> the sphere object structure to reflect onto
 * @return t_vector			-> the reflection vector
 *
 * @parent_func get_reflection_vector	-> function to reflect a ray on an object
 */
static t_vector	sphere_ref(t_ray ray, t_object sphere)
{
	t_vector	n;
	t_vector	r;

	n = subs_vec_coords(ray.coords, sphere.coords);
	n = normalise(n);
	if (dist(sphere.coords, ray.origin_coords)
		< sphere.special_data.sphere.radius)
		n = prod_vec_int(n, -1);
	r = calc_ref_form(ray.vector, n);
	return (r);
}

/*
 * Function to calculate the vector resulting from the reflection of a ray on a
 * plane object.
 *
 * @param t_ray ray			-> the ray to reflect
 * @param t_object plane	-> the plane object structure to reflect onto
 * @return t_vector			-> the reflection vector
 *
 * @parent_func get_reflection_vector	-> function to reflect a ray on an object
 */
static t_vector	plane_ref(t_ray ray, t_object plane)
{
	t_vector	n;
	t_vector	r;

	n = normalise(plane.orientation_vector);
	r = calc_ref_form(ray.vector, n);
	return (r);
}

/*
 * Function to calculate the vector resulting from the reflection of a ray on one
 * end of a cylinder object.
 *
 * @param t_ray ray			-> the ray to reflect
 * @param t_object cylinder	-> the cylinder object structure to reflect onto
 * @return t_vector			-> the reflection vector
 *
 * @parent_func get_reflection_vector	-> function to reflect a ray on an object
 */
static t_vector	cylinder_ext_ref(t_ray ray, t_object cylinder, int res)
{
	t_vector	n;
	t_vector	r;

	if (res == 4)
		n = normalise(cylinder.orientation_vector);
	else
		n = normalise(prod_vec_float(cylinder.orientation_vector, -1));
	r = calc_ref_form(ray.vector, n);
	return (r);
}

/*
 * Function to calculate the vector resulting from the reflection of a ray on the
 * side of a cylinder object.
 *
 * @param t_ray ray			-> the ray to reflect
 * @param t_object cylinder	-> the cylinder object structure to reflect onto
 * @return t_vector			-> the reflection vector
 *
 * @parent_func get_reflection_vector	-> function to reflect a ray on an object
 */
static t_vector	cylinder_side_ref(t_ray ray, t_object cylinder)
{
	t_vector	n;
	t_vector	r;
	t_coords	cp;
	t_basis		world_basis;
	t_ray		aligned_ray;

	world_basis = (t_basis){(t_vector){1, 0, 0}, (t_vector){0, 1, 0},
		(t_vector){0, 0, 1}};
	aligned_ray = switch_ray_basis(ray, cylinder.local_basis, world_basis);
	cylinder.coords = switch_coords_basis(cylinder.coords, cylinder.local_basis,
			world_basis);
	cp = advance_on_vec_z(cylinder.coords, aligned_ray.coords);
	n = normalise(subs_vec_coords(aligned_ray.coords, cp));
	r = calc_ref_form(aligned_ray.vector, n);
	return (switch_vector_basis(r, world_basis, cylinder.local_basis));
}

/*
 * Function to calculate the vector resulting from the reflection of a ray on an
 * object.
 *
 * @param t_ray ray		-> the ray to reflect
 * @param t_object obj	-> the object structure to reflect onto
 * @return t_vector		-> the reflection vector
 *
 * @child_func sphere_ref			-> function to reflect a ray on a sphere
 * @child_func plane_ref			-> function to reflect a ray on a plane
 * @child_func cylinder_side_ref	-> function to reflect a ray on a cyl. side
 * @child_func cylinder_ext_ref		-> function to reflect a ray on a cyl. end
 */
t_vector	get_reflection_vector(t_ray ray, t_object obj)
{
	t_vector	reflection_vec;

	if (obj.type == SPHERE_OBJ)
		return (reflection_vec = sphere_ref(ray, obj));
	if (obj.type == PLANE_OBJ)
		return (reflection_vec = plane_ref(ray, obj));
	if (obj.type == CYLINDER_OBJ && ray.res == 3)
		return (reflection_vec = cylinder_side_ref(ray, obj));
	if (obj.type == CYLINDER_OBJ && (ray.res == 4 || ray.res == 5))
		return (reflection_vec = cylinder_ext_ref(ray, obj, ray.res));
	return (ray.vector);
}
