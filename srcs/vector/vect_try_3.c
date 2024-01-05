/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:19 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/05 21:31:28 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	try_plan_cyl_inf(t_ray *ray, t_coords cp, t_object obj, int i)
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

void	try_plan_cyl_sup(t_ray *ray, t_coords cp, t_object obj, int i)
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

void	try_cylinder_ext(t_ray *ray, t_object obj, int i)
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

void	try_cylinder_side(t_ray *ray, t_object obj, int i)
{
	t_sol	s;
	float	delta;
	float	t;
	t_ray	aligned_ray;

	aligned_ray = switch_rb(ray, obj);
	obj.coords = switch_cb(obj);
	s = init_param(aligned_ray, obj);
	delta = pow(s.b, 2) - 4 * s.a * s.c;
	if (delta >= 0)
	{
		t = good_sol(delta, s.b, s.a);
		if (t >= 0 && (ray->res == 0 || t < ray->sol))
		{
			aligned_ray.coords = find_pos_touch(&aligned_ray, t - 0.1f);
			if (test(aligned_ray, obj) == 1)
				give_sol(&aligned_ray, t, i);
		}
	}
	*ray = switch_ray_basis(aligned_ray,
			(t_basis){{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, obj.local_basis);
	obj.coords = switch_coords_basis(obj.coords,
			(t_basis){{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, obj.local_basis);
	try_cylinder_ext(ray, obj, i);
}
