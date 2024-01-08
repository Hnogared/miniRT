/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:50:45 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/08 14:29:36 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to rotate a vector structure using a rotation matrix.
 * The rotation matrix can be calculated using get_rotation_matrix().
 *
 * Origin vector (v) = {x, y, z}
 * Rotated vector (v') = {x', y', z'}
 * Rotation matrix (R) = {{r00, r01, r02}, {r10, r11, r12}, {r20, r21, r22}}
 *
 * (v') = (R)(v)
 * x' ( res.x ) = r00 * x + r01 * y + r02 * z
 * y' ( res.y ) = r10 * x + r11 * y + r12 * z
 * z' ( res.z ) = r20 * x + r21 * y + r22 * z
 *
 * @param t_vector to_rotate		-> vector to rotate
 * @param float rot_matrix[3][3]	-> matrix used for the rotation
 * @return t_vector					-> the rotated vector
 */
t_vector	matrix_vector_rotation(t_vector to_rotate, float rot_matrix[3][3])
{
	t_vector	res;

	res.x = rot_matrix[0][0] * to_rotate.x + rot_matrix[0][1] * to_rotate.y
		+ rot_matrix[0][2] * to_rotate.z;
	res.y = rot_matrix[1][0] * to_rotate.x + rot_matrix[1][1] * to_rotate.y
		+ rot_matrix[1][2] * to_rotate.z;
	res.z = rot_matrix[2][0] * to_rotate.x + rot_matrix[2][1] * to_rotate.y
		+ rot_matrix[2][2] * to_rotate.z;
	return (res);
}

/*
 * Function to rotate a coordinates structure using a rotation matrix.
 * The rotation matrix can be calculated using get_rotation_matrix().
 *
 * Origin coords (c) = {x, y, z}
 * Rotated coords (c') = {x', y', z'}
 * Rotation matrix (R) = {{r00, r01, r02}, {r10, r11, r12}, {r20, r21, r22}}
 *
 * (c') = (R)(c)
 * x' ( res.x ) = r00 * x + r01 * y + r02 * z
 * y' ( res.y ) = r10 * x + r11 * y + r12 * z
 * z' ( res.z ) = r20 * x + r21 * y + r22 * z
 *
 * @param t_coords to_rotate		-> coordinates to rotate
 * @param float rot_matrix[3][3]	-> rotation matrix used for the roation
 * @return t_coords					-> the rotated coordinates
 */
t_coords	matrix_coords_rotation(t_coords to_rotate, float rot_matrix[3][3])
{
	t_coords	res;

	res.x = rot_matrix[0][0] * to_rotate.x + rot_matrix[0][1] * to_rotate.y
		+ rot_matrix[0][2] * to_rotate.z;
	res.y = rot_matrix[1][0] * to_rotate.x + rot_matrix[1][1] * to_rotate.y
		+ rot_matrix[1][2] * to_rotate.z;
	res.z = rot_matrix[2][0] * to_rotate.x + rot_matrix[2][1] * to_rotate.y
		+ rot_matrix[2][2] * to_rotate.z;
	return (res);
}

/*
 * Function to rotate a basis structure along a vector axis at a degrees angle.
 *
 * @param t_basis to_rotate	-> basis to rotate
 * @param float angle		-> angle of the rotation in degrees
 * @param t_vector axis		-> axis along which to rotate
 * @return t_basis			-> the rotated basis structure
 */
t_basis	axial_basis_rotation(t_basis to_rotate, float angle, t_vector axis)
{
	t_basis	rotated;

	rotated = to_rotate;
	if (prod_scal_vec(to_rotate.x, axis) != 1.0f)
		rotated.x = axial_vector_rotation(to_rotate.x, angle, axis);
	if (prod_scal_vec(to_rotate.y, axis) != 1.0f)
		rotated.y = axial_vector_rotation(to_rotate.y, angle, axis);
	if (prod_scal_vec(to_rotate.z, axis) != 1.0f)
		rotated.z = axial_vector_rotation(to_rotate.z, angle, axis);
	return (rotated);
}

/*
 * Function to rotate a vector structure along a vector axis at a degrees angle.
 *
 * Rotation matrix (R) = {{r00, r01, r02}, {r10, r11, r12}, {r20, r21, r22}}
 * Ø = angle in radians
 *
 * r00 ( rot_matrix[0][0] ) = cosØ + axis.u^2 * (1 - cosØ)
 * r01 ( rot_matrix[0][1] ) = axis.x * axis.y * (1 - cosØ) - axis.z * sinØ
 * r02 ( rot_matrix[0][2] ) = axis.x * axis.z * (1 - cosØ) + axis.y * sinØ
 *
 * r10 ( rot_matrix[1][0] ) = axis.y * axis.x * (1 - cosØ) + axis.z * sinØ
 * r11 ( rot_matrix[1][1] ) = cosØ + axis.y^2 * (1 - cosØ)
 * r12 ( rot_matrix[1][2] ) = axis.y * axis.z * (1 - cosØ) - axis.x * sinØ
 *
 * r20 ( rot_matrix[2][0] ) = axis.z * axis.x * (1 - cosØ) - axis.y * sinØ
 * r21 ( rot_matrix[2][1] ) = axis.z * axis.y * (1 - cosØ) + axis.x * sinØ
 * r22 ( rot_matrix[2][2] ) = cosØ + axis.z^2 * (1 - cosØ)
 *
 * Vector rotation (rot_vector) = (R)(vector) --> see matrix_vector_rotation()
 *
 * @param t_vector to_rotate	-> vector to rotate
 * @param float degree_angle	-> angle of the rotation in degrees
 * @return t_vector				-> the rotated vector structure
 */
t_vector	axial_vector_rotation(t_vector to_rotate, float degree_angle,
	t_vector axis)
{
	float	rad;
	float	ang_cos;
	float	ang_sin;
	float	rot_matrix[3][3];

	rad = to_rad(degree_angle);
	ang_cos = cos(rad);
	ang_sin = sin(rad);
	rot_matrix[0][0] = ang_cos + axis.x * axis.x * (1 - ang_cos);
	rot_matrix[0][1] = axis.x * axis.y * (1 - ang_cos) - axis.z * ang_sin;
	rot_matrix[0][2] = axis.x * axis.z * (1 - ang_cos) + axis.y * ang_sin;
	rot_matrix[1][0] = axis.y * axis.x * (1 - ang_cos) + axis.z * ang_sin;
	rot_matrix[1][1] = ang_cos + axis.y * axis.y * (1 - ang_cos);
	rot_matrix[1][2] = axis.y * axis.z * (1 - ang_cos) - axis.x * ang_sin;
	rot_matrix[2][0] = axis.z * axis.x * (1 - ang_cos) - axis.y * ang_sin;
	rot_matrix[2][1] = axis.z * axis.y * (1 - ang_cos) + axis.x * ang_sin;
	rot_matrix[2][2] = ang_cos + axis.z * axis.z * (1 - ang_cos);
	return (matrix_vector_rotation(to_rotate, rot_matrix));
}

/*
 * Function to initialize the parameter rotation matrix between two vectors.
 * The rotation starts from vector1 and ends at vector2.
 *
 * prod_scal_vec() --> dot product
 * prod_vec_vec() --> cross product
 *
 * @param float ro_matrix_to_set[3][3]	-> rotation matrix array to initialize
 * @param t_vector vector1				-> vector at the rotation start
 * @param t_vector vector2				-> vector at the rotation end
 */
void	get_rotation_matrix(float rot_matrix_to_set[3][3], t_vector vector1,
	t_vector vector2)
{
	float		cos;
	float		coeff;
	t_vector	axis;

	axis = prod_vec_vec(vector1, vector2);
	cos = prod_scal_vec(vector1, vector2);
	coeff = 1.0f / (1.0f + cos);
	rot_matrix_to_set[0][0] = (axis.x * axis.x * coeff) + cos;
	rot_matrix_to_set[0][1] = (axis.y * axis.x * coeff) - axis.z;
	rot_matrix_to_set[0][2] = (axis.z * axis.x * coeff) + axis.y;
	rot_matrix_to_set[1][0] = (axis.x * axis.y * coeff) + axis.z;
	rot_matrix_to_set[1][1] = (axis.y * axis.y * coeff) + cos;
	rot_matrix_to_set[1][2] = (axis.z * axis.y * coeff) - axis.x;
	rot_matrix_to_set[2][0] = (axis.x * axis.z * coeff) - axis.y;
	rot_matrix_to_set[2][1] = (axis.y * axis.z * coeff) + axis.x;
	rot_matrix_to_set[2][2] = (axis.z * axis.z * coeff) + cos;
}
