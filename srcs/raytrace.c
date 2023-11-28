/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/28 13:30:31 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Bien recu !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! =D
 *
 * hippo - "Teamwork hell yeah ;)"
 */

float	to_rad(float degree_angle)
{
	return ((degree_angle * PI) / 180);
}

/*
 * https://en.wikipedia.org/wiki/Rotation_matrix
 * Rotation matrix from axis and angle
 *
 * Vector to rotate (v):
 * ┌             ┐
 * | to_rotate.x |
 * | to_rotate.y |
 * | to_rotate.z |
 * └             ┘
 *
 *
 * Rotation matrix (R):
 * ┌             ┐
 * | r00 r01 r02 |
 * | r10 r11 r12 |
 * | r20 r21 r22 |
 * └             ┘
 * Ø = angle in radians
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
 *
 * Vector rotation (v') = (R)(v) :
 * see matrix_vector_rotation()
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
 * Vector v rotation using the matrix R | (v') = (R)(v) :
 * ┌    ┐   ┌             ┐┌   ┐
 * | x' |   | r00 r01 r02 || x |
 * | y' | = | r10 r11 r12 || y |
 * | z' |   | r20 r21 r22 || z |
 * └    ┘   └             ┘└   ┘
 * x' ( res.x ) = r00 * x + r01 * y + r02 * z
 * y' ( res.y ) = r10 * x + r11 * y + r12 * z
 * z' ( res.z ) = r20 * x + r21 * y + r22 * z
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
 * https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724
 * prod_scal_vec() = dot_product()
 * prod_vec_vec() = cross_product()
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

/*
 * TODO alloc error management
 */
t_ray	*horizontal_rays(int steps, int fov, t_orthonormal_basis basis,
	t_coords origin)
{
	int		i;
	float	horizontal_angle;
	t_ray	*rays;

	if (!steps)
		return (NULL);
	rays = (t_ray *) ft_calloc(steps, sizeof(t_ray));
	if (!rays)
		return (NULL);
	horizontal_angle = fov / steps;
	rays[steps / 2].vector = basis.x;
	rays[steps / 2].coords = origin;
	rays[steps / 2].origin_coords = origin;
	i = 0;
	while (i < steps / 2)
	{
		rays[steps / 2 - i - 1].vector
			= axial_vector_rotation(rays[steps / 2 - i].vector,
			horizontal_angle, basis.z);
		rays[steps / 2 - i - 1].coords = origin;
		rays[steps / 2 - i - 1].origin_coords = origin;
		print_vector(rays[steps / 2 - i - 1].vector);
		if (i == steps / 2 - 1 && steps % 2)
			break ;
		rays[steps / 2 + i + 1].vector
			= axial_vector_rotation(rays[steps / 2 + i].vector,
			360 - horizontal_angle, basis.z);
		rays[steps / 2 + i + 1].coords = origin;
		rays[steps / 2 + i + 1].origin_coords = origin;
		print_vector(rays[steps / 2 + i + 1].vector);
		i++;
	}
	return (rays);
}

int	camera_rays(t_data *data, t_object camera)
{
	float				vertical_angle;
	float				horizontal_angle;
	t_ray				**rays_tab;
	t_orthonormal_basis	temp_basis;

	rays_tab = (t_ray **) malloc((data->main_window.height / data->pixel_ratio)
			* sizeof(t_ray *));
	vertical_angle = 90 / data->main_window.height * data->pixel_ratio;
	horizontal_angle = camera.special_data.camera.fov
		/ data->main_window.height * data->pixel_ratio;
	temp_basis = camera.loc_basis;
	if ((data->main_window.height * data->pixel_ratio) % 2 == 0)
	{
		temp_basis.z = axial_vector_rotation(temp_basis.z, vertical_angle,
			temp_basis.y);
		temp_basis.x = axial_vector_rotation(temp_basis.x, vertical_angle,
			temp_basis.y);
	}
	if ((data->main_window.width * data->pixel_ratio) % 2 == 0)
	{
		temp_basis.x = axial_vector_rotation(temp_basis.x,
			360 - horizontal_angle / 2.0f, temp_basis.z);
		temp_basis.y = axial_vector_rotation(temp_basis.y,
			360 - horizontal_angle / 2.0f, temp_basis.z);
	}
	rays_tab[data->main_window.height / data->pixel_ratio / 2]
		= horizontal_rays(data->main_window.width / data->pixel_ratio,
		camera.special_data.camera.fov, temp_basis, camera.coords);
	free(rays_tab[data->main_window.height / data->pixel_ratio / 2]);
	free(rays_tab);
	return (0);
}
