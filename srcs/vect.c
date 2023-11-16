/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:48:18 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/14 10:48:20 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*P=O+t⋅D
Où :
P est le point d'intersection que tu cherches.
O est le point d'origine du rayon.
D est la direction normalisée du rayon.
t est le paramètre que tu dois déterminer.*/

/*at^2 + bt + c = 0;
a = ||D||^2;
b = 2 . (O - C).D 
c = || O - C ||^2 - r^2*/

t_coords    find_pos_sphere(t_data *data, t_object sphere, t_vector vec_inc, t_coords org)
{
    t_vector    n_inc;
    t_coords    p;
    int         a;
    int         b;
    int         c;
    int         r;
    int         sol1;
    int         sol2;

    n_inc = normalise(vec_inc);
    a = 1;
    b = prod_vec_int(prod_scal_vec(sous_vec_coord(org, sphere.coords), n_inc), 2);
    r = sphere.special_data.sphere.diameter / 2;
    c = pow(magnitude(sous_vec_coord(org, sphere.coords)), 2) * pow(r, 2);
    sol1 = (-1 * pow(b, 2) + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
    sol2 = (-1 * pow(b, 2) - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
    if (sol1 > = 0)
        return (p = add_vec_coord_vec(org, prod_vec_int(n_inc, sol1)));
    else
        return (p = add_vec_coord_vec(org, prod_vec_int(n_inc, sol2)));
}

t_vector    cal_sphere(t_data *data, t_vector vec_inc, t_coords origin)
{
    t_object    sphere;
    t_coords    pos;
    t_vector    n;
    t_vector    r;

    //sphere = fonction pour savoir quel sphere ?
    pos = find_pos_sphere(data, sphere, vec_inc, origin);
    n = sous_vec_coord(pos, sphere.coords);
    n = normalise(n);
    r = calc_ref_form(vec_inc, n);
    return (r);
}

t_vector    cal_plan(t_vector vec_inc, t_object plan)
{
    t_vector    n;
    t_vector    r;

    n = normalise(plan.orientation_vector);
    r = calc_ref_form(vec_inc, n);
    return (r);
}

t_vector    calcul_ref(t_data *data, t_vector vec_inc, t_object obj)
{
    t_vector    vec_ref;

    if (obj.type == SPHERE_OBJ)
		vec_ref = cal_sphere(data, vec_inc, origine);
	if (obj.type == PLANE_OBJ)
		vec_ref = cal_plan(vec_inc, obj);
	//if (obj.type == CYLINDER_OBJ)
	//	vec_ref = cal_cylinder(data, vec_inc);
    return (vec_ref);
}

int try_sphere(t_data *data, t_coords pos_test, t_object obj, t_vector vec_inc)
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
    ici origine du rayon est la position test = FAUX A AMELIORER !!!!.
    */

    float   a;
    float   b;
    float   c;
    float   delta;

    a = pow(magnitude(vec_inc), 2);
    b = 2 * prod_scal_vec(vec_inc, add_vec_coord(pos_test, prod_vec_int(obj.coords, -1)));
    c = pow(magnitude(pos_test), 2) + pow(magnitude(obj.coords), 2) - 2 * prod_scal_vec(obj.coords, pos_test) - pow((obj.special_data.sphere.diameter / 2), 2);

}

int	try_plan(t_coords pos_test, t_object plan)
{
    //equation a resoudre (ax + by + cz + d =0) avec vecteur normal du plan (donne dans le sujet) N(a, b, c) et d a determiner avec le point du plan (aussi donne dans le sujet)
    // d = -(ax + by + cz) avec toujours N(a, b, c) et (x, y, z) les coordonnees du point
    float   d;
    float   res;

    d = -(plan.orientation_vector.x * plan.coords.x + plan.orientation_vector.y * plan.coords.y + plan.orientation_vector.z * plan.coords.z);
    res = plan.orientation_vector.x * pos_test.x + plan.orientation_vector.y * pos_test.y + plan.orientation_vector.z * pos_test.z + d;
    if (res == 0)
        return (1);
    else
        return (0);
}

int	do_touch(t_data *data, t_coords pos_test, t_vector vec_inc, t_object obj)
{
	if (obj.type == SPHERE_OBJ)
		return (try_sphere(data, pos_test, obj, vec_inc));
	if (obj.type == PLANE_OBJ)
		return (try_plan(pos_test, obj, vec_inc));
	//if (obj.type == CYLINDER_OBJ)
	//	return (try_cylinder(data, vec_inc, obj));
}

t_vector    touch_object(t_data *data, t_vector vec_inc, t_coords pos_test)
{
    int         i;
    t_vector    vec_ref;

    i = 0;
    vec_ref = vec_inc;
    while (data->scene_objects[i])
    {
        if (do_touch(data, pos_test, vec_inc, data->scene_objects[i]) == 1)
        {
			vec_ref = calcul_ref(data, vec_inc, data->scene_objects[i]);
			break
        }
		i++;
    }
	return (vec_ref);
}
