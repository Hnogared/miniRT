/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2023/12/01 17:26:36 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	cal_sphere(t_ray *ray, t_object sphere)
{
	t_vector	n;
	t_vector	r;

	n = sous_vec_coord(ray->coords, sphere.coords);
	n = normalise(n);
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

	if (res == 2)
		n = normalise(cylindre.orientation_vector);
	else
		n = normalise(prod_vec_int(cylindre.orientation_vector, -1));
	r = calc_ref_form(ray->vector, n);
	return (r);
}

t_vector	cal_cylinder_side(t_ray *ray, t_object cylindre)
{
	t_vector	n;
	t_vector	r;
	t_coords	cp;
	float		d;

	//1ere etape, trouver le C', sachant que CP^2 = CC'^2 + r^2
	//donc CC' = CP^2 - r^2
	// et C' = C + CC'*N;
	
	d = pow(dist(ray->coords, cylindre.coords), 2) - pow(cylindre.special_data.cylinder.diameter / 2, 2);
	if (prod_scal_vec(cylindre.orientation_vector, sous_vec_coord(ray->coords, cylindre.coords)) >= 0)
		cp = advance_on_vec(cylindre.coords, cylindre.orientation_vector, d);
	else
		cp = advance_on_vec(cylindre.coords, prod_vec_int(cylindre.orientation_vector, -1), d);
	// comm d'hab, trouver le N et appliquer la formule.
	n = normalise(sous_vec_coord(ray->coords, cp));
	r = calc_ref_form(ray->vector, n);
	return (r);
}

t_vector	calcul_ref(t_ray *ray, t_object obj, int res)
{
	t_vector	vec_ref;

	if (obj.type == SPHERE_OBJ)
		vec_ref = cal_sphere(ray, obj);
	if (obj.type == PLANE_OBJ)
		vec_ref = cal_plan(ray, obj);
	if (obj.type == CYLINDER_OBJ && res == 1)
		vec_ref = cal_cylinder_side(ray, obj);
	if (obj.type == CYLINDER_OBJ && (res == 2 || res == 3))
		vec_ref = cal_cylinder_ext(ray, obj, res);
	//if (obj.type == CYLINDER_OBJ && res == 3)
	//	vec_ref = cal_cylinder_ext(ray, obj, res);
	return (vec_ref);
}

int	try_sphere(t_ray *ray, t_object obj)
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
		ray->coords = find_pos_touch(*ray, t);
		return (1);
	}
}

int	try_plan(t_ray *ray, t_object plan)
{
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
	float		d;
	//float	res;
	float		t;
	t_vector	n;

	n = normalise(plan.orientation_vector);
	d = -(n.x * plan.coords.x + n.y * plan.coords.y + n.z * plan.coords.z);
	//res = plan.orientation_vector.x * pos_test.x + plan.orientation_vector.y * pos_test.y + plan.orientation_vector.z * pos_test.z + d;
	//if (res == 0)
	//	return (1);
	t = -((prod_scal_vec_coord(n, ray->origin_coords) + d)/ prod_scal_vec(n, ray->vector));
	if (t > 0)
	{
		ray->coords = find_pos_touch(*ray, t);
		return (1);
	}
	else
		return (0);
}

int	try_plan_cyl(t_ray *ray, t_coords cp, t_vector n, t_object obj)
{
	float		d;
	float		t;
	float		verif;
	t_vector	nn;

	nn = normalise(n);
	d = -(nn.x * cp.x + nn.y * cp.y + nn.z * cp.z);
	t = -((prod_scal_vec_coord(nn, ray->origin_coords) + d)/ prod_scal_vec(nn, ray->vector));
	if (t > 0)
	{
		ray->coords = find_pos_touch(*ray, t);
		verif = dist(ray->coords, cp);
		if (verif < obj.special_data.cylinder.diameter / 2)
			return (1);
	}
	return (0);
}

int	try_cylinder_ext(t_ray *ray, t_object obj)
{
	// faire comme avec un plan avec N le vecteur de l'axe du cylindre et le point sera la projection de C sur le plan.
	// H/2, on peut retrouver C' pour les 2 cas C'sup et C'inf;
	t_coords	cps;
	t_coords	cpi;

	cps = advance_on_vec(obj.coords, obj.orientation_vector, obj.special_data.cylinder.height / 2);
	cpi = advance_on_vec(obj.coords, obj.orientation_vector, - obj.special_data.cylinder.height / 2);

    // teste comme avec un plan mais on doit trouver une solutin et que la distance pos_test - C'sup ou pos_test - C'inf soit inferieur a r;
	if (try_plan_cyl(ray, cps, obj.orientation_vector, obj) == 1)
		return (2);
	if (try_plan_cyl(ray, cpi, obj.orientation_vector, obj) == 1)
		return (3);
	else
		return (0);
}

int	try_cylinder_side(t_ray *ray, t_object obj)
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
	float	t;

	k = prod_scal_vec(obj.orientation_vector, ray->vector);
	h = prod_scal_vec(obj.orientation_vector, sous_vec_coord(ray->origin_coords, obj.coords));
	a = pow(k, 2);	
	b = 2 * k * h;
	c = pow(h, 2) - pow(obj.special_data.cylinder.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (try_cylinder_ext(ray, obj));
	else // une solution existe sur un cylindre infini --> doic verifier que l'on est dans la hauteur du cylindre !.
	{
		//Or, on obtient un triangle rectangle entre P, C et la projection de P sur l'axe du cylindre (on va l'appeler L), rectangle en L.
		//Donc PC^2 = LP^2 + CL^2.
		//On sait aussi que, au max, CL = H/2; et que LP vaut toujours r;
		// PC^2 ne peut pas etre > (H/2)^2 + r^2 --> sinon, pas sur notre cylindre;
		t = good_sol(delta, b, a);
		ray->coords = find_pos_touch(*ray, t);
		if (pow(dist(ray->coords, obj.coords), 2) <= (pow(obj.special_data.cylinder.height / 2, 2) + pow(obj.special_data.cylinder.diameter / 2, 2)))
			return (1);
		else
			return (try_cylinder_ext(ray, obj));
	}	
}

int	do_touch(t_ray *ray, t_object obj)
{
	if (obj.type == SPHERE_OBJ)
		return (try_sphere(ray, obj));
	else if (obj.type == PLANE_OBJ)
		return (try_plan(ray, obj));
	else if (obj.type == CYLINDER_OBJ)
		return (try_cylinder_side(ray, obj));
	else
		return (0);
}

void	touch_object(t_data *data, t_ray *ray)
{
	unsigned short	i;
	int	res;

	i = 0;
	//vec_ref = vec_inc;
	while (i < data->obj_count)
	{
		res = do_touch(ray, data->scene_objects[i]);
		printf("res vaut %d\n", res);
		if (res >= 1)
		{
			ray->vector = calcul_ref(ray, data->scene_objects[i], res);
			ray->origin_coords = give_coord(ray->coords);
			ray->touch = 1;
			ray->nb_ref++;
			ray->objects_touch[ray->s++] = data->scene_objects[i];
			return ;
		}
		i++;
	}
	ray->touch = 0;
	//ray->objects_touch[ray->s++] = NULL;
	return ;
}

void	ray_advance(t_data *data, t_ray *ray)
{
	ray->touch = 1;
	ray->nb_ref = 0;
	ray->s = 0;
	ray->objects_touch = malloc(sizeof(t_object) * 4);
	while (ray->touch != 0 && ray->nb_ref <= 2)
		touch_object(data, ray);
	printf("** %d ** ", ray->nb_ref);
	print_vector(ray->vector);
	printf(" ");
	print_coords(ray->origin_coords);
	printf("\n");
}
