/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:03:20 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/15 11:03:21 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector    sous_vec_coord(t_coords a, t_coords b)
{
    t_vector    c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;

    return (c);
}

t_vector    add_vec_coord(t_coords a, t_coords b)
{
    t_vector    c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;

    return (c);
}

t_vector    sous_vec_vec(t_vector a, t_vector b)
{
    t_vector    c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;

    return (c);
}

t_vector    add_vec_vec(t_vector a, t_vector b)
{
    t_vector    c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;

    return (c);
}

t_coords    add_vec_coord_vec(t_coords a, t_vector b)
{
    t_coords   c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;

    return (c);
}

t_vector    prod_vec_int(t_vector a, int k)
{
    t_vector    c;

    c.x = a.x * k;
    c.y = a.y * k;
    c.z = a.z * k;

    return (c);
}

int    prod_scal_vec(t_vector a, t_vector b)
{
    int    c;

    c = a.x * b.x + a.y * b.y + a.z * b.z;

    return (c);
}

t_vector    prod_vec_vec(t_vector a, t_vector b)
{
    t_vector    c;

    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;

    return (c);
}

t_vector calc_ref_form(t_vector i, t_vector n)
{
    t_vector   r;
	int		scal;

	scal = prod_scal_vec(i, n);
	r = sous_vec_vec(i, prod_vec_int(n, 2*scal));
	return (r);
}

int	magnitude(t_vector n)
{
	int			a;
	int			nxc;
	int			nyc;
    int			nzc;
    t_vector	nn;

    nxc = pow(n.x, 2);
    nyc = pow(n.y, 2);
    nyz = pow(n.z, 2);
    a = sqrt(nxc + nyc + nyz);
	return (a);
}

int	normalise(t_vector n)
{
	int			a;
	
    a = magnitude(n);
    if (a == 1)
        return (n);
    else
    {
		nn.x = n.x / a;
		nn.y = n.y / a;
		nn.z = n.z / a;
		return (nn);
    }
}

int dist(t_coords a, t_coords b)
{
    int x;
    int y;
    int z;

    x = pow((b.x - a.x), 2);
    y = pow((b.y - a.y), 2);
    z = pow((b.z - a.z), 2);

    return (sqrt(x + y + z));
}