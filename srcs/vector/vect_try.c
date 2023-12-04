/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_try.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:10 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/29 16:37:12 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
int	try_sphere(t_ray *ray, t_object obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;

	a = pow(magnitude(ray->vector), 2);
	b = 2 * prod_scal_vec(ray->vector, sous_vec_coord(ray->origin_coords, obj.coords));
	c = pow(magnitude_coord(ray->origin_coords), 2) + pow(magnitude_coord(obj.coords), 2) - 2 * prod_scal_coord(obj.coords, ray->origin_coords) - pow((obj.special_data.sphere.diameter / 2), 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (0);
	else
	{
		t = good_sol(delta, b, a);
		ray->coords = find_pos_touch(ray, t);
		return (1);
	}
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
revient a verifier si t = - (N.O)/(N.D) > 0;
*/
int	try_plan(t_ray *ray, t_object plan)
{
	float		d;
	float		t;
	t_vector	n;

	n = normalise(plan.orientation_vector);
	d = -(n.x * plan.coords.x + n.y * plan.coords.y + n.z * plan.coords.z);
	t = -((prod_scal_vec_coord(n, ray->origin_coords) + d) / prod_scal_vec(n, ray->vector));
	if (t > 0)
	{
		ray->coords = find_pos_touch(ray, t);
		return (1);
	}
	else
		return (0);
}
