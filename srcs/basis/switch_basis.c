/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_basis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:59:56 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 11:21:34 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 *
 */
static bool	check_vector_equality(t_vector vector1, t_vector vector2)
{
	return (vector1.x == vector2.x && vector1.y == vector2.y
		&& vector1.z == vector2.z);
}

t_ray	switch_ray_basis(t_ray to_rotate, t_basis new_basis, t_basis old_basis)
{
	float	rot_matrix[3][3];
	t_ray	res;

	if (check_vector_equality(new_basis.x, old_basis.x)
		&& check_vector_equality(new_basis.y, old_basis.y)
		&& check_vector_equality(new_basis.z, old_basis.z))
		return (to_rotate);
	get_rotation_matrix(rot_matrix, old_basis.z, new_basis.z);
	ft_memmove(&res, &to_rotate, sizeof(t_ray));
	res.origin_coords = matrix_coords_rotation(to_rotate.origin_coords,
			rot_matrix);
	res.coords = matrix_coords_rotation(to_rotate.coords, rot_matrix);
	res.vector = matrix_vector_rotation(to_rotate.vector, rot_matrix);
	return (res);
}

t_coords	switch_coords_basis(t_coords to_rotate, t_basis new_basis,
	t_basis old_basis)
{
	float	rot_matrix[3][3];

	if (check_vector_equality(new_basis.x, old_basis.x)
		&& check_vector_equality(new_basis.y, old_basis.y)
		&& check_vector_equality(new_basis.z, old_basis.z))
		return (to_rotate);
	get_rotation_matrix(rot_matrix, old_basis.z, new_basis.z);
	return (matrix_coords_rotation(to_rotate, rot_matrix));
}

t_vector	switch_vector_basis(t_vector to_rotate, t_basis new_basis,
	t_basis old_basis)
{
	float	rot_matrix[3][3];

	if (check_vector_equality(new_basis.x, old_basis.x)
		&& check_vector_equality(new_basis.y, old_basis.y)
		&& check_vector_equality(new_basis.z, old_basis.z))
		return (to_rotate);
	get_rotation_matrix(rot_matrix, old_basis.z, new_basis.z);
	return (matrix_vector_rotation(to_rotate, rot_matrix));
}
