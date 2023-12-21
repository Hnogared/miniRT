/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthonormal_basis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/21 17:18:25 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the x axis.
 *
 * @param t_vector xxx_orientation	-> the new basis' x axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
t_basis	get_ortho_basis_from_x(t_vector xxx_orientation)
{
	t_vector	z_axis;
	t_basis		new;

	new.x = normalise(xxx_orientation);
	z_axis = (t_vector){0, 0, 1};
	if (!xxx_orientation.x && !xxx_orientation.y
		&& (xxx_orientation.z == 1.0f || xxx_orientation.z == -1.0f))
		new.z = (t_vector){-1 * xxx_orientation.z, 0, 0};
	else
	{
		new.z = prod_vec_float(new.x, prod_scal_vec(new.x, z_axis));
		new.z = normalise(sous_vec_vec(z_axis, new.z));
	}
	new.y = normalise(prod_vec_vec(new.z, new.x));
	return (new);
}

/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the y axis.
 *
 * @param t_vector xxx_orientation	-> the new basis' y axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
t_basis	get_ortho_basis_from_y(t_vector y_orientation)
{
	t_vector	x_axis;
	t_basis		new;

	new.y = normalise(y_orientation);
	x_axis = (t_vector){1, 0, 0};
	if (!y_orientation.y && !y_orientation.z
		&& (y_orientation.x == 1.0f || y_orientation.x == -1.0f))
		new.x = (t_vector){0, -1 * y_orientation.x, 0};
	else
	{
		new.x = prod_vec_float(new.y, prod_scal_vec(new.y, x_axis));
		new.x = normalise(sous_vec_vec(x_axis, new.x));
	}
	new.z = normalise(prod_vec_vec(new.x, new.y));
	return (new);
}

/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the z axis.
 *
 * @param t_vector z_orientation	-> the new basis' z axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
t_basis	get_ortho_basis_from_z(t_vector z_orientation)
{
	t_vector	y_axis;
	t_basis		new;

	new.z = normalise(z_orientation);
	y_axis = (t_vector){0, 1, 0};
	if (!z_orientation.x && !z_orientation.z
		&& (z_orientation.y == 1.0f || z_orientation.y == -1.0f))
		new.y = (t_vector){0, 0, -1 * z_orientation.y};
	else
	{
		new.y = prod_vec_float(new.z, prod_scal_vec(new.z, y_axis));
		new.y = normalise(sous_vec_vec(y_axis, new.y));
	}
	new.x = normalise(prod_vec_vec(new.y, new.z));
	return (new);
}
