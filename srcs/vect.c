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

t_vector    cal_plan(t_data *data, t_vector vec_inc, t_coords origin)
{
    t_vector    n;
    t_vector    r;
    t_object    plan;

    //plan = fonction pour savoir quel sphere ?
    n = normalise(plan.orientation_vector);
    r = calc_ref_form(vec_inc, n);
    return (r);
}

t_vector    calcul_ref(t_data *data, t_vector vec_inc, t_coords origin)
{
    unsigned short	type;
    t_vector    vec_ref;

    type == 3;
    //type = fonction pour savoit si ca touche les objets 
    /*if(type == BLANK_OBJ)
        vec_ref = cal_blank(data, vec_inc);
    if(type == CAMERA_OBJ)
        vec_ref = cal_camera(data, vec_inc);
    if(type == LIGHT_OBJ)
        vec_ref = cal_light(data, vec_inc);*/
    if(type == SPHERE_OBJ)
        //vec_ref = cal_sphere(data, vec_inc, origine);
    if(type == PLANE_OBJ)
        //vec_ref = cal_plan(data, vec_inc);
    if(type == CYLINDER_OBJ)
        //vec_ref = cal_cylinder(data, vec_inc);
    return (vec_ref);
}

t_vector    touch_object(t_data *data, t_vector vec_inc, t_coords pos_test)
{
    int         i;
    t_vector    vec_ref;

    i = 0;
    while (data->scene_objects[i])
    {
        if ()
    }
}
