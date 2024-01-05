/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_basis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:59:56 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 15:22:16 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return true if two vectors are the same, false otherwise.
 *
 * @param t_vector vector1	-> the first vector structure to compare
 * @param t_vector vector2	-> the second vector structure to compare
 * @return bool				-> the result of the comparison
 */
static bool	check_vector_equality(t_vector vector1, t_vector vector2)
{
	return (vector1.x == vector2.x && vector1.y == vector2.y
		&& vector1.z == vector2.z);
}

/*
 * Function to transpose a t_ray structure from one basis to another.
 * If the bases are the same, return the original ray.
 *
 * @param t_ray to_rotate	-> ray structure to modify for the transposition
 * @param t_basis new_basis	-> the basis into which the ray is converted
 * @param t_basis old_basis	-> the basis from which the ray is converted
 * @return t_ray			-> the new transposed ray
 */
t_ray	switch_ray_basis(t_ray to_rotate, t_basis new_basis, t_basis old_basis)
{
	float	rot_matrix[3][3];
	t_ray	res;

	if (check_vector_equality(new_basis.x, old_basis.x)
		&& check_vector_equality(new_basis.y, old_basis.y)
		&& check_vector_equality(new_basis.z, old_basis.z))
		return (to_rotate);
	get_rotation_matrix(rot_matrix, new_basis.z, old_basis.z);
	ft_memmove(&res, &to_rotate, sizeof(t_ray));
	res.origin_coords = matrix_coords_rotation(to_rotate.origin_coords,
			rot_matrix);
	res.coords = matrix_coords_rotation(to_rotate.coords, rot_matrix);
	res.vector = matrix_vector_rotation(to_rotate.vector, rot_matrix);
	return (res);
}

/*
 * Function to transpose a t_coords structure from one basis to the other.
 * If the bases are the same, return the original coordinates.
 *
 * @param t_coords to_rotate-> coords structure to modify for the transposition
 * @param t_basis new_basis	-> the basis into which the coords are converted
 * @param t_basis old_basis	-> the basis from which the coords are converted
 * @return t_coords			-> the new transposed coordinates
 */
t_coords	switch_coords_basis(t_coords to_rotate, t_basis new_basis,
	t_basis old_basis)
{
	float	rot_matrix[3][3];

	if (check_vector_equality(new_basis.x, old_basis.x)
		&& check_vector_equality(new_basis.y, old_basis.y)
		&& check_vector_equality(new_basis.z, old_basis.z))
		return (to_rotate);
	get_rotation_matrix(rot_matrix, new_basis.z, old_basis.z);
	return (matrix_coords_rotation(to_rotate, rot_matrix));
}

/*
 * Function to transpose a t_vector structure from one basis to the other.
 * If the bases are the same, return the original vector.
 *
 * @param t_vector to_rotate-> vector structure to modify for the transposition
 * @param t_basis new_basis	-> the basis into which the vector is converted
 * @param t_basis old_basis	-> the basis from which the vector is converted
 * @return t_vector			-> the new transposed vector
 */
t_vector	switch_vector_basis(t_vector to_rotate, t_basis new_basis,
	t_basis old_basis)
{
	float	rot_matrix[3][3];

	if (check_vector_equality(new_basis.x, old_basis.x)
		&& check_vector_equality(new_basis.y, old_basis.y)
		&& check_vector_equality(new_basis.z, old_basis.z))
		return (to_rotate);
	get_rotation_matrix(rot_matrix, new_basis.z, old_basis.z);
	return (matrix_vector_rotation(to_rotate, rot_matrix));
}
