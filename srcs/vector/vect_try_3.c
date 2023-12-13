/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:19 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/29 16:37:20 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	try_plan_cyl_inf(t_ray *ray, t_coords cp, t_vector n, t_object obj, int i)
{
	float		d;
	float		t;
	float		verif;
	t_vector	nn;

	nn = normalise(n);
	nn = prod_vec_float(nn, -1);
	d = -(nn.x * cp.x + nn.y * cp.y + nn.z * cp.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d) / prod_scal_vec(nn, ray->vector));
	if (t >= 0)
	{
		if (ray->res == 0 && t != -1)
		{
			ray->coords = find_pos_touch(ray, t);
			verif = dist(cp, ray->coords);
			if (verif <= obj.special_data.cylinder.diameter / 2)
			{
				ray->sol = t;
				ray->res = 5;
				ray->go = i;
				//return (1);
			}
		}
		else if (t < ray->sol && t != -1)
		{
			ray->coords = find_pos_touch(ray, t);
			verif = dist(cp, ray->coords);
			if (verif <= obj.special_data.cylinder.diameter / 2)
			{
				ray->sol = t;
				ray->res = 5;
				ray->go = i;
				//return (1);
			}	
		}
	}
	//return (0);
}

void	try_plan_cyl_sup(t_ray *ray, t_coords cp, t_vector n, t_object obj, int i)
{
	float		d;
	float		t;
	float		verif;
	t_vector	nn;

	nn = normalise(n);
	d = -(nn.x * cp.x + nn.y * cp.y + nn.z * cp.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d) / prod_scal_vec(nn, ray->vector));
	t -= 0.1f;
	if (t >= 0)
	{
		if (ray->res == 0 && t != -1)
		{
			ray->coords = find_pos_touch(ray, t);
			verif = dist(cp, ray->coords);
			if (verif <= obj.special_data.cylinder.diameter / 2)
			{
				ray->sol = t;
				ray->res = 4;
				ray->go = i;
				//return (1);
			}
		}
		else if (t < ray->sol && t != -1)
		{
			ray->coords = find_pos_touch(ray, t);
			verif = dist(cp, ray->coords);
			if (verif <= obj.special_data.cylinder.diameter / 2)
			{
				ray->sol = t;
				ray->res = 4;
				ray->go = i;
				//return (1);
			}	
		}
	}
	//return (0);
}

void	try_cylinder_ext(t_ray *ray, t_object obj, int i)
{
	t_coords	cps;
	t_coords	cpi;

	cps = advance_on_vec(obj.coords, obj.orientation_vector, obj.special_data.cylinder.height / 2);
	cpi = advance_on_vec(obj.coords, obj.orientation_vector, -obj.special_data.cylinder.height / 2);
	try_plan_cyl_sup(ray, cps, obj.orientation_vector, obj, i);
		//return (2);
	try_plan_cyl_inf(ray, cpi, obj.orientation_vector, obj, i);
		//return (3);
	//else
	//	return (0);
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

void	try_cylinder_side(t_ray *ray, t_object obj, int i)
{
	float	a;
	float	b;
	float	c;
	float	ox;
	float	oy;
	float	dx;
	float	dy;
	float	delta;
	float	t;

	
	ox = ray->origin_coords.x;
	oy = ray->origin_coords.y;
	dx = ray->vector.x;
	dy = ray->vector.y;
	a = pow(dx, 2) + pow(dy, 2);
	b = 2 * (ox * dx + oy * dy - dx * obj.coords.x - dy * obj.coords.y);
	c = ox * ox - 2 * obj.coords.x * ox + pow(obj.coords.x, 2) + oy * oy - 2 * obj.coords.y * oy + pow(obj.coords.y, 2) - pow(obj.special_data.cylinder.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	//printf("Delta vaut : %f\n", delta);
	if (delta >= 0)
	{
		//printf("Delta vaut : %f\n", delta);
		//return (try_cylinder_ext(ray, obj));
		t = good_sol(delta, b, a);
		//printf("sol vaut :%f\n", t);
		ray->coords = find_pos_touch(ray, t);
		//if (pow(dist(ray->coords, obj.coords), 2) <= 1250)
		//	printf("ok pour une valeur de %f\n", pow(dist(ray->coords, obj.coords), 2));
		//printf("dist test vaut :%f\n", pow(dist(ray->coords, obj.coords), 2));
		//printf("H/2 vaut :%f\n", pow(obj.special_data.cylinder.height / 2, 2));
		//printf("rayon vaut :%f\n", pow(obj.special_data.cylinder.diameter / 2, 2));
		//printf("somme de H/2 et r vaut :%f\n\n\n", pow(obj.special_data.cylinder.height / 2, 2) + pow(obj.special_data.cylinder.diameter / 2, 2));
		/*if (pow(dist(obj.coords, ray->coords), 2) <= (pow(obj.special_data.cylinder.height / 2, 2) + pow(obj.special_data.cylinder.diameter / 2, 2)) && t != -1)
		{
			//return (1);
			ray->sol = t;
			ray->res = 3;
			ray->go = i;
			//printf("yes !!!!! sol =%f res = %d \n", ray->sol, ray->res);
			//return (try_cylinder_ext(ray, obj));
		}*/
		if (ray->coords.z <= (obj.coords.z + obj.special_data.cylinder.height / 2) && ray->coords.z >= (obj.coords.z - obj.special_data.cylinder.height / 2))
		{
			ray->sol = t;
			ray->res = 3;
			ray->go = i;
		}
	}
		//else
			//return (try_cylinder_ext(ray, obj));
	//return ;
	try_cylinder_ext(ray, obj, i);
}
