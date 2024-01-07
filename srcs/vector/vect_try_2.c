/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:19 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/07 01:48:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	try_plan_cyl_inf(t_ray *ray, t_coords cp, t_object obj, int i)
{
	float		d;
	float		t;
	t_coords	touch_pos;
	t_vector	nn;
	t_vector	n;

	n = obj.orientation_vector;
	nn = normalise(n);
	nn = prod_vec_float(nn, -1);
	d = -(nn.x * cp.x + nn.y * cp.y + nn.z * cp.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d));
	t = t / prod_scal_vec(nn, ray->vector);
	if (t >= 0 && (ray->res == 0 || t < ray->sol))
	{
		touch_pos = find_pos_touch(ray, t - 0.1f);
		if (dist(cp, touch_pos) > obj.special_data.cylinder.radius + 0.01f)
			return ;
		ray->coords = touch_pos;
		ray->sol = t;
		ray->res = 5;
		ray->go = i;
	}
}

static void	try_plan_cyl_sup(t_ray *ray, t_coords cp, t_object obj, int i)
{
	float		d;
	float		t;
	t_coords	touch_pos;
	t_vector	nn;
	t_vector	n;

	n = obj.orientation_vector;
	nn = normalise(n);
	d = -(nn.x * cp.x + nn.y * cp.y + nn.z * cp.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d));
	t = t / prod_scal_vec(nn, ray->vector);
	if (t >= 0 && (ray->res == 0 || t < ray->sol))
	{
		touch_pos = find_pos_touch(ray, t - 0.1f);
		if (dist(cp, touch_pos) > obj.special_data.cylinder.radius + 0.01f)
			return ;
		ray->coords = touch_pos;
		ray->sol = t;
		ray->res = 4;
		ray->go = i;
	}
}

static void	try_cylinder_ext(t_ray *ray, t_object obj, int i)
{
	t_coords	cps;
	t_coords	cpi;

	cps = advance_on_vec(obj.coords, obj.orientation_vector,
			obj.special_data.cylinder.height / 2);
	cpi = advance_on_vec(obj.coords, obj.orientation_vector,
			-obj.special_data.cylinder.height / 2);
	try_plan_cyl_sup(ray, cps, obj, i);
	try_plan_cyl_inf(ray, cpi, obj, i);
}

/*pour cylindre side test avec cylindre centre sur z.

    equationa resoudre
    P=O+t⋅D
    Où :
    P est le point d'intersection.
    O est le point d'origine du rayon.
    D est la direction normalisée du rayon.
    t est le paramètre a déterminer.

	equation d'un cylindre centre sur (a,b) de rayon r.
	(x-a)^2 + (y-b)^2= r^2;
	avec :
	
	at^2 + bt + c;
	avec 
	a = dx^2 + dy^2;
	b = 2 * (0xdx + Oydy -Dxa - Dyb)
	c = (Ox - a)^2 + (Oy - b)^2 - r^2;
	
*/
/*
t_sol	init_param(t_ray aligned_ray, t_object obj)
{
	t_sol	s;

	s.ox = aligned_ray.origin_coords.x;
	s.oy = aligned_ray.origin_coords.y;
	s.dx = aligned_ray.vector.x;
	s.dy = aligned_ray.vector.y;
	s.a = pow(s.dx, 2) + pow(s.dy, 2);
	s.b = s.ox * s.dx + s.oy * s.dy - s.dx * obj.coords.x;
	s.b = s.b - s.dy * obj.coords.y;
	s.b = 2 * s.b;
	s.c = s.ox * s.ox - 2 * obj.coords.x * s.ox;
	s.c = s.c + pow(obj.coords.x, 2) + s.oy * s.oy;
	s.c = s.c - 2 * obj.coords.y * s.oy + pow(obj.coords.y, 2);
	s.c = s.c - pow(obj.special_data.cylinder.radius, 2);
	return (s);
}
*/
float	calc_vertical_cylinder_side(t_ray ray, t_object obj, float params[4])
{
	float	o_coos[2];
	float	r_vec[2];

	o_coos[0] = ray.origin_coords.x;
	o_coos[1] = ray.origin_coords.y;
	r_vec[0] = ray.vector.x;
	r_vec[1] = ray.vector.y;
	params[0] = r_vec[0] * r_vec[0] + r_vec[1] * r_vec[1];
	params[1] = o_coos[0] * r_vec[0] + o_coos[1] * r_vec[1];
	params[1] = 2 * (params[1] - r_vec[0] * obj.coords.x - r_vec[1]
			* obj.coords.y);
	params[2] = o_coos[0] * o_coos[0] - 2 * obj.coords.x * o_coos[0];
	params[2] = params[2] + obj.coords.x * obj.coords.x + o_coos[1] * o_coos[1];
	params[2] = params[2] - 2 * obj.coords.y * o_coos[1] + obj.coords.y
		* obj.coords.y;
	params[2] = params[2] - obj.special_data.cylinder.radius
		* obj.special_data.cylinder.radius;
	params[3] = params[1] * params[1] - 4 * params[0] * params[2];
	return (params[3]);
}

void	try_cylinder(t_ray *ray, t_object obj, int i)
{
	float		t;
	t_ray		aligned_ray;
	t_basis		world_basis;
	float		params[4];

	world_basis = (t_basis){{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	aligned_ray = switch_ray_basis(*ray, obj.local_basis, world_basis);
	obj.coords = switch_coords_basis(obj.coords, obj.local_basis, world_basis);
	if (calc_vertical_cylinder_side(aligned_ray, obj, params) >= 0)
	{
		t = good_sol(params[3], params[1], params[0]);
		if (t >= 0 && (ray->res == 0 || t < ray->sol))
		{
			aligned_ray.coords = find_pos_touch(&aligned_ray, t - 0.1f);
			if (aligned_ray.coords.z <= (obj.coords.z
					+ (obj.special_data.cylinder.height + 0.1f) / 2)
				&& aligned_ray.coords.z >= (obj.coords.z
					- (obj.special_data.cylinder.height + 0.1f) / 2))
				give_sol(&aligned_ray, t, i);
		}
	}
	*ray = switch_ray_basis(aligned_ray, world_basis, obj.local_basis);
	obj.coords = switch_coords_basis(obj.coords, world_basis, obj.local_basis);
	try_cylinder_ext(ray, obj, i);
}
