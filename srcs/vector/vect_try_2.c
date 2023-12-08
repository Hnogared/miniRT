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

/*pour cylindre side

    equationa resoudre
    P=O+t⋅D
    Où :
    P est le point d'intersection.
    O est le point d'origine du rayon.
    D est la direction normalisée du rayon.
    t est le paramètre a déterminer.

	equation d'un cylindre infini 
	(N.(P - C))^2 = r^2;
	avec :
	N le vecteur normal de son axe;
	P la position a tester
	C les coordonnes du centre du cylindre 
	et r le rayon du cylindre
	*/

	/*pour trouver t, equation a resoudre :
    (N.((O+t⋅D) - C))^2 = r^2

	ce qui ammene a 
    at^2 + bt + c = 0;

    a = (N.D)^2 
    b = 2 * (N.D) * (N.(O-C)) 
    c = (N.(O-C))^2 - r^2

	si k = N.D
	et h = N.(O-C)

	alors
	a = k^2 
    b = 2 * k * h 
    c = h^2 - r^2
	delta = B^2 - 4AC; si pas de solution dans le reel (= delta < 0) alors pas d'intersection.

    pour plus de precision, voir cahier.

    si une solution existe : // une solution existe sur un cylindre infini --> doic verifier que l'on est dans la hauteur du cylindre !
    //Or, on obtient un triangle rectangle entre P, C et la projection de P sur l'axe du cylindre (on va l'appeler L), rectangle en L.
	//Donc PC^2 = LP^2 + CL^2.
	//On sait aussi que, au max, CL = H/2; et que LP vaut toujours r;
	// PC^2 ne peut pas etre > (H/2)^2 + r^2 --> sinon, pas sur notre cylindre;

    sinon test ext:
    // faire comme avec un plan avec N le vecteur de l'axe du cylindre et le point sera la projection de C sur le plan.
	// H/2, on peut retrouver C' pour les 2 cas C'sup et C'inf;

    // teste comme avec un plan mais on doit trouver une solutin et que la distance pos_test - C'sup ou pos_test - C'inf soit inferieur a r;
*/

void	try_plan_cyl_inf(t_ray *ray, t_coords cp, t_vector n, t_object obj, int i)
{
	float		d;
	float		t;
	float		verif;
	t_vector	nn;

	nn = normalise(n);
	d = -(nn.x * cp.x + nn.y * cp.y + nn.z * cp.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d) / prod_scal_vec(nn, ray->vector));
	if (t >= 0)
	{
		if (ray->res == -1 )
		{
			ray->coords = find_pos_touch(ray, t);
			verif = dist(ray->coords, cp);
			if (verif < obj.special_data.cylinder.diameter / 2)
			{
				ray->sol = t;
				ray->res = 5;
				ray->go = i;
				//return (1);
			}
		}
		else if (ray->res == 1 || ray->res == 2)
		{
			if (t < ray->sol)
			{
				ray->coords = find_pos_touch(ray, t);
				verif = dist(ray->coords, cp);
				if (verif < obj.special_data.cylinder.diameter / 2)
				{
					ray->sol = t;
					ray->res = 5;
					ray->go = i;
					//return (1);
				}
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
	if (t >= 0)
	{
		if (ray->res == -1 )
		{
			ray->coords = find_pos_touch(ray, t);
			verif = dist(ray->coords, cp);
			if (verif < obj.special_data.cylinder.diameter / 2)
			{
				ray->sol = t;
				ray->res = 4;
				ray->go = i;
				//return (1);
			}
		}
		else if (ray->res == 1)
		{
			if (t < ray->sol)
			{
				ray->coords = find_pos_touch(ray, t);
				verif = dist(ray->coords, cp);
				if (verif < obj.special_data.cylinder.diameter / 2)
				{
					ray->sol = t;
					ray->res = 4;
					ray->go = i;
					//return (1);
				}	
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

void	try_cylinder_side(t_ray *ray, t_object obj, int i)
{
	float	a;
	float	b;
	float	c;
	float	k;
	float	h;
	float	delta;
	float	t;

	k = prod_scal_vec(obj.orientation_vector, ray->vector);
	h = prod_scal_vec(obj.orientation_vector, sous_vec_coord(ray->origin_coords, obj.coords));
	a = pow(k, 2);
	b = 2 * k * h;
	c = pow(h, 2) - pow(obj.special_data.cylinder.diameter / 2, 2);
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
		if (pow(dist(ray->coords, obj.coords), 2) <= (pow(obj.special_data.cylinder.height / 2, 2) + pow(obj.special_data.cylinder.diameter / 2, 2)))
		{
			//return (1);
			ray->sol = t;
			ray->res = 3;
			ray->go = i;
			//printf("yes !!!!! sol =%f res = %d \n", ray->sol, ray->res);
			//return (try_cylinder_ext(ray, obj));
		}
	}
		//else
			//return (try_cylinder_ext(ray, obj));
	try_cylinder_ext(ray, obj, i);
}
