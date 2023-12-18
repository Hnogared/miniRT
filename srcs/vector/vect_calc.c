/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:35:57 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/29 16:35:58 by tlorne           ###   ########.fr       */
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
	if (dist(sphere.coords, ray->origin_coords) < sphere.special_data.sphere.diameter / 2)
		n = prod_vec_float(n, -1);
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

t_vector	cal_cylinder_side(t_ray *ray, t_object cylindre)
{
	t_vector	n;
	t_vector	r;
	t_coords	cp;
	//float		d;

	//d = pow(dist(ray->coords, cylindre.coords), 2) - pow(cylindre.special_data.cylinder.diameter / 2, 2);
	//if (prod_scal_vec(cylindre.orientation_vector, sous_vec_coord(ray->coords, cylindre.coords)) >= 0)
	//	cp = advance_on_vec(cylindre.coords, cylindre.orientation_vector, d);
	/*if (cylindre.coords.z <= ray->coords.z)
		cp = advance_on_vec_z_sup(cylindre.coords, cylindre.orientation_vector, d);
	else
	{
		cp = advance_on_vec_z_inf(cylindre.coords, cylindre.orientation_vector, d);
		printf("\n cp vaut :");
		print_coord(cp);
		printf("\n ray->coords vaut :");
		print_coord(ray->coords);
	}*/
	cp = advance_on_vec_z(cylindre.coords, ray->coords);
	n = normalise(sous_vec_coord(ray->coords, cp));
	r = calc_ref_form(ray->vector, n);
	/*if (cylindre.coords.z > ray->coords.z)
	{
		printf("\n n vaut :");
		print_vec(n);
		printf("\n r vaut :");
		print_vec(r);
	}*/
	return (r);
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
