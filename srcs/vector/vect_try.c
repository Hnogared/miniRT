/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:10 by tlorne            #+#    #+#             */
/*   Updated: 2023/12/13 17:10:26 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*equation a resoudre
P=O+t⋅D avec le p les coordones de la light
xl   Ox       Dx
yl = Oy + t x Dy
zl   Oz       Dz

3 expressions de t, si toutes identiques, ca touche.
si t = (xl - Ox) / Dx == (yl - Oy)/ Dy == (zl - Oz) / dz;
alors ca touche !
*/
void	try_light(t_ray *ray, t_object obj, int i)
{
/*	float	t1;
	float	t2;
	float	t3;

	t1 = (l.coords.x - ray->origin_coords.x) / ray->vector.x;
	t2 = (l.coords.y - ray->origin_coords.y) / ray->vector.y;
	t3 = (l.coords.z - ray->origin_coords.z) / ray->vector.z;
	if (t1 == t2 && t1 == t3)
	{
		if (ray->res == 0)
		{
			//ray->coords = find_pos_touch(ray, t);
			ray->sol = t1;
			ray->res = 7;
			ray->go = i;
			ray->tl = 1;
		}
		else if (t1 <= ray->sol)
		{
			//ray->coords = find_pos_touch(ray, t);
			ray->sol = t1;
			ray->res = 7;
			ray->go = i;
			ray->tl = 1;
		}
	}*/

	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;

	a = pow(magnitude(ray->vector), 2);
	b = 2 * prod_scal_vec(ray->vector, sous_vec_coord(ray->origin_coords, obj.coords));
	c = pow(magnitude_coord(ray->origin_coords), 2) + pow(magnitude_coord(obj.coords), 2) - 2 * prod_scal_coord(obj.coords, ray->origin_coords) - pow((obj.special_data.light.radius), 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		t = good_sol(delta, b, a);
		if (t >= 0 && (ray->res == 0 || t < ray->sol))
		{
			ray->coords = find_pos_touch(ray, t - 0.001f);
			ray->sol = t;
			ray->res = 2;
			ray->go = i;
		}
		//return (0);
	}
	/*else
	{
		return (1);
	}*/
}

/*equationa resoudre
P=O+t⋅D
Où :
P est le point d'intersection.
O est le point d'origine du rayon.
D est la direction normalisée du rayon.
t est le paramètre a déterminer.*/

/*equation d'une sphere :
(x-a)^2 + (y−b)^2 + (z-c)^2 = r^2.
Où (a,b,c) est le centre de la sphère, et r le rayon.
*/

/*pour trouver t, equation a resoudre :
((Ox+t⋅Dx) - a)^2 + ((Oy+t⋅Dy) - b)^2 + ((Oz+t⋅Dz) - c)^2.
at^2 + bt + c = 0;
a = ||D||^2;
b = 2 x D.(O - C) 
c = ||O||^2 + ||C||^2 -2x(C.O) - r^2
    
C = centre de la sphere et r son rayon.

delta = B^2 - 4AC; si pas de solution dans le reel (= delta < 0) alors pas d'intersection.

pour plus de precision, voir cahier.
ici origine du rayon est la position test = FAUX A AMELIORER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.
*/
void	try_sphere(t_ray *ray, t_object obj, int i)
{
//	t_vector	vec;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;

	a = 1;
//	a = pow(magnitude(ray->vector), 2);
	b = 2 * prod_scal_vec(ray->vector, sous_vec_coord(ray->origin_coords, obj.coords));
	c = pow(magnitude_coord(ray->origin_coords), 2) + pow(magnitude_coord(obj.coords), 2) - 2 * prod_scal_coord(obj.coords, ray->origin_coords) - pow((obj.special_data.sphere.radius), 2);
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		t = good_sol(delta, b, a);
		if (t >= 0 && (ray->res == 0 || t < ray->sol))
		{
			ray->coords = find_pos_touch(ray, t - 0.001f);
			ray->sol = t;
			ray->res = 2;
			ray->go = i;
		}
	}

	/*
	vec = sous_vec_coord(ray->origin_coords, obj.coords);
	b = 2 * prod_scal_vec(ray->vector, a);
	c = prod_scal_vec(vec, vec) - obj.special_data.sphere.radius * obj.special_data.sphere.radius;
	delta = b * b - 4 * c;
	if (delta >= 0)
	{
		if ()
	}
	*/

		//return (0);
	/*else
	{
		return (1);
	}*/
}

//equation a resoudre (ax + by + cz + d =0) avec vecteur normal du plan (donne dans le sujet) N(a, b, c) et d a determiner avec le point du plan (aussi donne dans le sujet)
// d = -(ax + by + cz) avec toujours N(a, b, c) et (x, y, z) les coordonnees du point
/*equationa resoudre
P=O+t⋅D
Où :
P est le point d'intersection.
O est le point d'origine du rayon.
D est la direction normalisée du rayon.
t est le paramètre a déterminer.*/

/*si il existe un t > 0 qui resout (a[Ox + t * Dx] + b[Oy + t * Dy] + c[Oz + t * Dz] + d =0)
alors ok.
revient a verifier si t = - [(N.O) + d]/(N.D) > 0;
*/
void	try_plan(t_ray *ray, t_object plan, int i)
{
	float		d;
	float		t;
	t_vector	n;

	//printf("test plan\n");
	n = normalise(plan.orientation_vector);
	//printf("n du plan vaut \n");
	//print_vec(n);
	//printf("vecteur du ray vaut \n");
	//print_vec(ray->vector);
	d = -(n.x * plan.coords.x + n.y * plan.coords.y + n.z * plan.coords.z);
	//printf("d vaut : %f\n", d);
	t = -((prod_scal_vec_coord(n, ray->origin_coords) + d) / prod_scal_vec(n, ray->vector));
//	t -= 0.1f;
	//printf("scal de N et 0 vaut %f\n", prod_scal_vec_coord(n, ray->origin_coords));
	//printf("scal de N et D vaut %f\n", prod_scal_vec(n, ray->vector));
	//printf("t vaut %f\n",t);
	if (t >= 0)
	{
		if (ray->res == 0 || t < ray->sol)
		{
			ray->coords = find_pos_touch(ray, t - 0.001f);
			ray->sol = t;
			ray->res = 1;
			ray->go = i;
		}
		//return (1);
	}
	//else
	//	return (0);
}
