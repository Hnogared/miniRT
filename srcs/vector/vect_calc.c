/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:35:57 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/05 11:30:06 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*pour cylinder side*/
//1ere etape, trouver le C', sachant que CP^2 = CC'^2 + r^2
//donc CC' = CP^2 - r^2
// et C' = C + CC'*N;

t_vector	cal_sphere(t_ray *ray, t_object sphere)
{
	t_vector	n;
	t_vector	r;

	n = sous_vec_coord(ray->coords, sphere.coords);
	n = normalise(n);
	if (dist(sphere.coords, ray->origin_coords)
		< sphere.special_data.sphere.radius)
		n = prod_vec_int(n, -1);
	r = calc_ref_form(ray->vector, n);
	return (r);
}

t_vector	cal_plan(t_ray *ray, t_object plan)
{
	t_vector	n;
	t_vector	r;

	n = normalise(plan.orientation_vector);
	r = calc_ref_form(ray->vector, n);
	return (r);
}

t_vector	cal_cylinder_ext(t_ray *ray, t_object cylindre, int res)
{
	t_vector	n;
	t_vector	r;

	if (res == 4)
		n = normalise(cylindre.orientation_vector);
	else
		n = normalise(prod_vec_float(cylindre.orientation_vector, -1));
	r = calc_ref_form(ray->vector, n);
	return (r);
}

t_vector	cal_cylinder_side(t_ray *ray, t_object cylinder)
{
	t_vector	n;
	t_vector	r;
	t_coords	cp;
	t_basis		world_basis;
	t_ray		aligned_ray;

	world_basis = (t_basis){(t_vector){1, 0, 0}, (t_vector){0, 1, 0},
		(t_vector){0, 0, 1}};
	aligned_ray = switch_ray_basis(*ray, cylinder.local_basis, world_basis);
	cylinder.coords = switch_coords_basis(cylinder.coords, cylinder.local_basis,
			world_basis);
	cp = advance_on_vec_z(cylinder.coords, aligned_ray.coords);
	n = normalise(sous_vec_coord(aligned_ray.coords, cp));
	r = calc_ref_form(aligned_ray.vector, n);
	return (switch_vector_basis(r, world_basis, cylinder.local_basis));
}

t_vector	calcul_ref(t_ray *ray, t_object obj, int res)
{
	t_vector	vec_ref;

	if (obj.type == SPHERE_OBJ)
		vec_ref = cal_sphere(ray, obj);
	if (obj.type == PLANE_OBJ)
		vec_ref = cal_plan(ray, obj);
	if (obj.type == CYLINDER_OBJ && res == 3)
		vec_ref = cal_cylinder_side(ray, obj);
	if (obj.type == CYLINDER_OBJ && (res == 4 || res == 5))
		vec_ref = cal_cylinder_ext(ray, obj, res);
	return (vec_ref);
}
