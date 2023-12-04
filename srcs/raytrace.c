/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/23 23:02:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * /!\ /!\ /!\ IMPORTANT
 * TODO enlever toute cette function declaration lorsque la vraie fonction dans
 * le fichier de Theo sera compilee.
 * Sinon ca compile pas vraiment mdr tavu, tu peux l'effacer tkt Theo j'en
 * avais juste besoin ASAP pour les fonctions en dessous c'est pour ca que je
 * te l'ai temporairement volee (empruntee) ici.

 Bien recu !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! =D
 */
/*float	prod_scal_vec(t_vector a, t_vector b)
{
	float	c;

	c = a.x * b.x + a.y * b.y + a.z * b.z;
	return (c);
}*/

/*
 * /!\ /!\ /!\ IMPORTANT
 * TODO enlever aussi cette declaration, decidement je voulais vraiment pas que
 * ca compile.
 */
/*t_vector	prod_vec_vec(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}*/

/*
 * /!\ /!\ /!\ IMPORTANT
 * TODO celle la aussi dsl :/
 */
/*float	magnitude(t_vector n)
{
	float		a;
	float		nxc;
	float		nyc;
	float		nzc;

	nxc = pow(n.x, 2);
	nyc = pow(n.y, 2);
	nzc = pow(n.z, 2);
	a = sqrt(nxc + nyc + nzc);
	return (a);
}*/

/*
 * /!\ /!\ /!\ IMPORTANT
 * TODO une derniere sur la route ptdr
 */
/*t_vector	normalise(t_vector n)
{
	float	a;

	a = magnitude(n);
	if (a == 1)
		return (n);
	else
	{
		n.x = n.x / a;
		n.y = n.y / a;
		n.z = n.z / a;
		return (n);
	}
}
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
	return (normalise(res));
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
