/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/18 15:49:12 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	cal_sphere(t_vector vec_inc, t_object sphere, t_coords pos_test)
{
	t_vector	n;
	t_vector	r;

	n = sous_vec_coord(pos_test, sphere.coords);
	n = normalise(n);
	r = calc_ref_form(vec_inc, n);
	return (r);
}

t_vector	cal_plan(t_vector vec_inc, t_object plan)
{
	t_vector	n;
	t_vector	r;

	n = normalise(plan.orientation_vector);
	r = calc_ref_form(vec_inc, n);
	return (r);
}

t_vector	cal_cylinder_ext(t_vector vec_inc, t_object cylindre, int res)
{
	t_vector	n;
	t_vector	r;

	if (res == 2)
		n = normalise(cylindre.orientation_vector);
	else
		n = normalise(prod_vec_int(cylindre.orientation_vector, -1));
	r = calc_ref_form(vec_inc, n);
}

t_vector	cal_cylinder_side(t_vector vec_inc, t_object cylindre, t_coords pos_test)
{
	t_vector	n;
	t_vector	r;
	t_coords	cp;
	float		d;

	//1ere etape, trouver le C', sachant que CP^2 = CC'^2 + r^2
	//donc CC' = CP^2 - r^2
	// et C' = C + CC'*N;

	d = pow(distance(pos_test, cylindre.coords), 2) - pow(cylindre.special_data.cylinder.diameter / 2, 2);
	cp = advance_on_vec(cylindre.coords, cylindre.orientation_vector, d);

	// comm d'hab, trouver le N et appliquer la formule.
	n = normalise(sous_vec_coord(pos_test, cp));
	r = calc_ref_form(vec_inc, n);
	return (r);
}

t_vector	calcul_ref(t_vector vec_inc, t_object obj, t_coords pos_test, int res)
{
	t_vector	vec_ref;

	if (obj.type == SPHERE_OBJ)
		vec_ref = cal_sphere(vec_inc, obj, pos_test);
	if (obj.type == PLANE_OBJ)
		vec_ref = cal_plan(vec_inc, obj);
	if (obj.type == CYLINDER_OBJ && res == 1)
		vec_ref = cal_cylinder_side(vec_inc, obj, pos_test);
	if (obj.type == CYLINDER_OBJ && res == 2)
		vec_ref = cal_cylinder_ext(vec_inc, obj, res);
	if (obj.type == CYLINDER_OBJ && res == 3)
		vec_ref = cal_cylinder_ext(vec_inc, obj, res);
	return (vec_ref);
}

int	try_sphere(t_coords pos_test, t_object obj, t_vector vec_inc)
{
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
	float	a;
	float	b;
	float	c;
	float	delta;

	a = pow(magnitude(vec_inc), 2);
	b = 2 * prod_scal_vec(vec_inc, add_vec_coord(pos_test, prod_vec_int(obj.coords, -1)));
	c = pow(magnitude(pos_test), 2) + pow(magnitude(obj.coords), 2) - 2 * prod_scal_vec(obj.coords, pos_test) - pow((obj.special_data.sphere.diameter / 2), 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (0);
	else
		return (1);
}

int	try_plan(t_coords pos_test, t_object plan)
{
    //equation a resoudre (ax + by + cz + d =0) avec vecteur normal du plan (donne dans le sujet) N(a, b, c) et d a determiner avec le point du plan (aussi donne dans le sujet)
    // d = -(ax + by + cz) avec toujours N(a, b, c) et (x, y, z) les coordonnees du point
	float	d;
	float	res;

	d = -(plan.orientation_vector.x * plan.coords.x + plan.orientation_vector.y * plan.coords.y + plan.orientation_vector.z * plan.coords.z);
	res = plan.orientation_vector.x * pos_test.x + plan.orientation_vector.y * pos_test.y + plan.orientation_vector.z * pos_test.z + d;
	if (res == 0)
		return (1);
	else
		return (0);
}

int	try_plan_cyl(t_coords pos_test, t_coords cp, t_vector n, t_object obj)
{
	float	d;
	float	res;
	float	verif;

	d = -(n.x * cp.x + n.y * cp.y + n * cp.z);
	res = n.x * pos_test.x + n.y * pos_test.y + n.z * pos_test.z + d;
	if (res == 0) // une solution existe, on doit verifier pos_test - C'sup ou pos_test - C'inf soit inferieur a r;
	{
		verif = distance(pos_test, cp);
		if (verif < obj.special_data.cylinder.diameter / 2)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	try_cylinder_ext(t_coords pos_test, t_vector vec_inc, t_object obj)
{
	// faire comme avec un plan avec N le vecteur de l'axe du cylindre et le point sera la projection de C sur le plan.
	// H/2, on peut retrouver C' pour les 2 cas C'sup et C'inf;
	t_coords	cps;
	t_coords	cpi;

	cps = advance_on_vec(obj.coords, obj.orientation_vector, obj.special_data.cylinder.height / 2);
	cpi = advance_on_vec(obj.coords, obj.orientation_vector, - obj.special_data.cylinder.height / 2);

    // teste comme avec un plan mais on doit trouver une solutin et que la distance pos_test - C'sup ou pos_test - C'inf soit inferieur a r;
	if (try_plan_cyl(pos_test, cps, obj.orientation_vector, obj) == 1)
		return (2);
	if (try_plan_cyl(pos_test, cpi, obj.orientation_vector, obj) == 1)
		return (3);
	else
		return (0);
}

int	try_cylinder_side(t_coords pos_test, t_vector vec_inc, t_object obj)
{
	/*equationa resoudre
    P=O+t⋅D
    Où :
    P est le point d'intersection.
    O est le point d'origine du rayon.
    D est la direction normalisée du rayon.
    t est le paramètre a déterminer.*/

	/*equation d'un cylindre infini 
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

    pour plus de precision, voir cahier.*/

	float	a;
	float	b;
	float	c;
	float	k;
	float	h;
	float	delta;

	k = prod_scal_vec(obj.orientation_vector, vec_inc);
	h = prod_scal_vec(obj.orientation_vector, sous_vec_coord(pos_test, obj.coords));
	a = pow(k, 2);	
	b = 2 * k * h;
	c = pow(h, 2) - pow(obj.special_data.cylinder.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (try_cylinder_ext(pos_test, vec_inc, obj));
	else // une solution existe sur un cylindre infini --> doic verifier que l'on est dans la hauteur du cylindre !.
	{
		//Or, on obtient un triangle rectangle entre P, C et la projection de P sur l'axe du cylindre (on va l'appeler L), rectangle en L.
		//Donc PC^2 = LP^2 + CL^2.
		//On sait aussi que, au max, CL = H/2; et que LP vaut toujours r;
		// PC^2 ne peut pas etre > (H/2)^2 + r^2 --> sinon, pas sur notre cylindre;
		if (dist(pos_test, obj.coords) <= (pow(obj.special_data.cylinder.height / 2, 2) + pow(obj.special_data.cylinder.diameter / 2, 2)))
			return (1);
		else
			return (try_cylinder_ext(pos_test, vec_inc, obj));
	}	
}

int	do_touch(t_coords pos_test, t_vector vec_inc, t_object obj)
{
	if (obj.type == SPHERE_OBJ)
		return (try_sphere(pos_test, obj, vec_inc));
	if (obj.type == PLANE_OBJ)
		return (try_plan(pos_test, obj, vec_inc));
	if (obj.type == CYLINDER_OBJ)
		return (try_cylinder_side(pos_test, vec_inc, obj));
}

t_vector	touch_object(t_data *data, t_vector vec_inc, t_coords pos_test)
{
	int			i;
	t_vector	vec_ref;
	int			res;

	i = 0;
	vec_ref = vec_inc;
	while (data->scene_objects[i])
	{
		res = do_touch(pos_test, vec_inc, data->scene_objects[i]);
		if (res >= 1)
		{
			vec_ref = calcul_ref(vec_inc, data->scene_objects[i], pos_test, res);
			break ;
		}
		i++;
	}
	return (vec_ref);
}
