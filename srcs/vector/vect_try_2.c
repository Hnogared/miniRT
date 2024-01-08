/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:19 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/08 16:24:28 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to trace a ray, check if it touches a cylinder's top side in relative
 * to its orientation vector and update it if true.
 *
 * @param t_ray *ray		-> pointer to the ray to test and update
 * @param t_coords side_pos	-> coordinates of the side center
 * @param t_object cylinder	-> cylinder object to check the collision with
 * @param int i				-> objects array index of the object struct
 *
 * @parent_func try_cylinder_ext	-> function to test a [cy-ends]-ray collision
 */
static void	try_plane_cyl_sup(t_ray *ray, t_coords side_pos, t_object cylinder,
	int i)
{
	float		d;
	float		t;
	t_coords	touch_pos;
	t_vector	nn;
	t_vector	n;

	n = cylinder.orientation_vector;
	nn = normalise(n);
	d = -(nn.x * side_pos.x + nn.y * side_pos.y + nn.z * side_pos.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d));
	t = t / prod_scal_vec(nn, ray->vector);
	if (t >= 0 && (ray->res == 0 || t < ray->sol))
	{
		touch_pos = find_pos_touch(ray, t - 0.1f);
		if (dist(side_pos, touch_pos)
			> cylinder.special_data.cylinder.radius + 0.01f)
			return ;
		ray->coords = touch_pos;
		ray->sol = t;
		ray->res = 4;
		ray->go = i;
	}
}

/*
 * Function to trace a ray, check if it touches a cylinder's bottom side relative
 * to its orientation vector and update it if true.
 *
 * @param t_ray *ray		-> pointer to the ray to test and update
 * @param t_coords side_pos	-> coordinates of the side center
 * @param t_object cylinder	-> cylinder object to check the collision with
 * @param int i				-> objects array index of the object struct
 *
 * @parent_func try_cylinder_ext	-> function to test a [cy-ends]-ray collision
 */
static void	try_plane_cyl_inf(t_ray *ray, t_coords side_pos, t_object cylinder,
	int i)
{
	float		d;
	float		t;
	t_coords	touch_pos;
	t_vector	nn;
	t_vector	n;

	n = cylinder.orientation_vector;
	nn = normalise(n);
	nn = prod_vec_float(nn, -1);
	d = -(nn.x * side_pos.x + nn.y * side_pos.y + nn.z * side_pos.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d));
	t = t / prod_scal_vec(nn, ray->vector);
	if (t >= 0 && (ray->res == 0 || t < ray->sol))
	{
		touch_pos = find_pos_touch(ray, t - 0.1f);
		if (dist(side_pos, touch_pos)
			> cylinder.special_data.cylinder.radius + 0.01f)
			return ;
		ray->coords = touch_pos;
		ray->sol = t;
		ray->res = 5;
		ray->go = i;
	}
}

/*
 * Function to trace a ray, check if it touches a cylinder's bottom or top side
 * relative to its orientation vector and update it if true.
 *
 * @param t_ray *ray		-> pointer to the ray to test and update
 * @param t_object cylinder	-> cylinder object to check the collision with
 * @param int i				-> objects array index of the object struct
 *
 * @child_func try_plane_cyl_sup-> function to test a [cy-top]-ray collision
 * @child_func try_plane_cyl_inf-> function to test a [cy-inf]-ray collision
 * @parent_func try_cylinder	-> function to test a cylinder-ray collision
 */
static void	try_cylinder_ext(t_ray *ray, t_object cylinder, int i)
{
	t_coords	sup_side_pos;
	t_coords	inf_side_pos;

	sup_side_pos = advance_on_vec(cylinder.coords, cylinder.orientation_vector,
			cylinder.special_data.cylinder.height / 2);
	inf_side_pos = advance_on_vec(cylinder.coords, cylinder.orientation_vector,
			-cylinder.special_data.cylinder.height / 2);
	try_plane_cyl_sup(ray, sup_side_pos, cylinder, i);
	try_plane_cyl_inf(ray, inf_side_pos, cylinder, i);
}

/*
	pour cylindre side test avec cylindre centre sur z.

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
 * Function to trace a ray, check if it touches a z axis aligned cylinder's
 * cylindrical side and return the result.
 *
 * @param t_ray ray		-> the ray to test for collision
 * @param t_object cyl	-> cylinder object to check the collision with
 * @param int i			-> objects array index of the object struct
 */
static float	try_vertical_cylinder_side(t_ray ray, t_object cyl)
{
	float	delta;
	float	params[3];
	float	o_coos[2];
	float	r_vec[2];

	ft_memmove(o_coos, (float [2]){ray.origin_coords.x, ray.origin_coords.y},
		sizeof(o_coos));
	ft_memmove(r_vec, (float [2]){ray.vector.x, ray.vector.y}, sizeof(r_vec));
	params[0] = r_vec[0] * r_vec[0] + r_vec[1] * r_vec[1];
	params[1] = o_coos[0] * r_vec[0] + o_coos[1] * r_vec[1];
	params[1] = 2 * (params[1] - r_vec[0] * obj.coords.x - r_vec[1]
			* cyl.coords.y);
	params[2] = o_coos[0] * o_coos[0] - 2 * cyl.coords.x * o_coos[0];
	params[2] = params[2] + cyl.coords.x * cyl.coords.x + o_coos[1] * o_coos[1];
	params[2] = params[2] - 2 * cyl.coords.y * o_coos[1] + cyl.coords.y
		* cyl.coords.y;
	params[2] = params[2] - cyl.special_data.cylinder.radius
		* cyl.special_data.cylinder.radius;
	delta = params[1] * params[1] - 4 * params[0] * params[2];
	if (delta < 0)
		return (-1.0f);
	return (good_sol(delta, params[1], params[0]));
}

/*
 *
 * @child_func try_cylinder_ext	-> function to test a [cy-ends]-ray collision
 */
void	try_cylinder(t_ray *ray, t_object obj, int i)
{
	float		res;
	t_ray		aligned_ray;
	t_basis		world_basis;

	world_basis = (t_basis){{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	aligned_ray = switch_ray_basis(*ray, obj.local_basis, world_basis);
	obj.coords = switch_coords_basis(obj.coords, obj.local_basis, world_basis);
	res = try_vertical_cylinder_side(aligned_ray, obj);
	if (res >= 0 && (ray->res == 0 || res < ray->sol))
	{
		aligned_ray.coords = find_pos_touch(&aligned_ray, res - 0.1f);
		if (aligned_ray.coords.z <= (obj.coords.z
				+ (obj.special_data.cylinder.height + 0.1f) / 2)
			&& aligned_ray.coords.z >= (obj.coords.z
				- (obj.special_data.cylinder.height + 0.1f) / 2))
		{
			aligned_ray.sol = res;
			aligned_ray.res = 3;
			aligned_ray.go = i;
		}
	}
	*ray = switch_ray_basis(aligned_ray, world_basis, obj.local_basis);
	obj.coords = switch_coords_basis(obj.coords, world_basis, obj.local_basis);
	try_cylinder_ext(ray, obj, i);
}
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
