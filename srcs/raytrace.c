/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/23 19:07:38 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	to_rad(float degree_angle)
{
	return ((degree_angle * PI) / 180);
}

/*
 * https://en.wikipedia.org/wiki/Rotation_matrix
 * Rotation matrix from axis and angle
 *
 * Vector to rotate (v):
 * ┌   ┐
 * | x |
 * | y |
 * | z |
 * └   ┘
 * x = to_rotate.x
 * y = to_rotate.y
 * z = to_rotate.z
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
 * ┌    ┐   ┌             ┐┌   ┐
 * | x' |   | r00 r01 r02 || x |
 * | y' | = | r10 r11 r12 || y |
 * | z' |   | r20 r21 r22 || z |
 * └    ┘   └             ┘└   ┘
 * x' ( res.x ) = r00 * x + r01 * y + r02 * z
 * y' ( res.y ) = r10 * x + r11 * y + r12 * z
 * z' ( res.z ) = r20 * x + r21 * y + r22 * z
 */
t_vector	rotate_vector(t_vector to_rotate, float degree_angle, t_vector axis)
{
	float		rot_matrix[3][3];
	float		rad;
	t_vector	res;

	rad = to_rad(degree_angle);
	rot_matrix[0][0] = cos(rad) + pow(axis.x, 2) * (1 - cos(rad));
	rot_matrix[0][1] = axis.x * axis.y * (1 - cos(rad)) - axis.z * sin(rad);
	rot_matrix[0][2] = axis.x * axis.z * (1 - cos(rad)) + axis.y * sin(rad);
	rot_matrix[1][0] = axis.y * axis.x * (1 - cos(rad)) + axis.z * sin(rad);
	rot_matrix[1][1] = cos(rad) + pow(axis.y, 2) * (1 - cos(rad));
	rot_matrix[1][2] = axis.y * axis.z * (1 - cos(rad)) - axis.x * sin(rad);
	rot_matrix[2][0] = axis.z * axis.x * (1 - cos(rad)) - axis.y * sin(rad);
	rot_matrix[2][1] = axis.z * axis.y * (1 - cos(rad)) + axis.x * sin(rad);
	rot_matrix[2][2] = cos(rad) + pow(axis.z, 2) * (1 - cos(rad));
	res.x = rot_matrix[0][0] * to_rotate.x + rot_matrix[0][1] * to_rotate.y
		+ rot_matrix[0][2] * to_rotate.z;
	res.y = rot_matrix[1][0] * to_rotate.x + rot_matrix[1][1] * to_rotate.y
		+ rot_matrix[1][2] * to_rotate.z;
	res.z = rot_matrix[2][0] * to_rotate.x + rot_matrix[2][1] * to_rotate.y
		+ rot_matrix[2][2] * to_rotate.z;
	return (res);
}

int	camera_rays(t_data *data, t_object camera)
{
	t_ray	*rays_tab;

	rays_tab = (t_ray *) malloc((data->main_window.width
				* data->main_window.height / data->pixel_ratio)
			* sizeof(t_ray));
	free(rays_tab);
	(void) camera;
	return (0);
}
