/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:57:14 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/08 14:30:06 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

/* ************************************************************************** */
/* rotation.c                                                                 */
/* ************************************************************************** */
/*
 * Function to rotate a vector structure using a rotation matrix.
 * The rotation matrix can be calculated using get_rotation_matrix().
 *
 * @param t_vector to_rotate		-> vector to rotate
 * @param float rot_matrix[3][3]	-> matrix used for the rotation
 * @return t_vector					-> the rotated vector
 */
t_vector	matrix_vector_rotation(t_vector to_rotate, float rot_matrix[3][3]);

/*
 * Function to rotate a coordinates structure using a rotation matrix.
 * The rotation matrix can be calculated using get_rotation_matrix().
 *
 * @param t_coords to_rotate		-> coordinates to rotate
 * @param float rot_matrix[3][3]	-> matrix used for the rotation
 * @return t_coords					-> the rotated coordinates
 */
t_coords	matrix_coords_rotation(t_coords to_rotate, float rot_matrix[3][3]);

/*
 * Function to rotate a basis structure along an axis at a given angle.
 *
 * @param t_basis to_rotate	-> basis to rotate
 * @param float angle		-> angle of the rotation in degrees
 * @param t_vector axis		-> axis along which to rotate
 * @return t_basis			-> the rotated basis structure
 */
t_basis		axial_basis_rotation(t_basis to_rotate, float angle, t_vector axis);

/*
 * Function to rotate a vector structure along a vector axis at a degrees angle.
 *
 * @param t_vector to_rotate	-> vector to rotate
 * @param float degree_angle	-> angle of the rotation in degrees
 * @return t_vector				-> the rotated vector structure
 */
t_vector	axial_vector_rotation(t_vector to_rotate, float angle,
				t_vector axis);

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
void		get_rotation_matrix(float rot_matrix_to_set[3][3], t_vector vector1,
				t_vector vector2);

/* ************************************************************************** */
/* rotation_2.c                                                               */
/* ************************************************************************** */
float		to_rad(float degree_angle);
t_vector	prod_vec_float(t_vector a, float k);

/* ************************************************************************** */
/* vect.c                                                                     */
/* ************************************************************************** */
int			do_touch(t_ray *ray, t_object obj, int i);
void		ray_advance(const t_data *data, t_ray *ray);

/* ************************************************************************** */
/* vect_calc.c                                                                */
/* ************************************************************************** */
t_vector	calcul_ref(const t_ray *ray, t_object obj, int res);

/* ************************************************************************** */
/* vect_try.c                                                                 */
/* ************************************************************************** */
void		try_light(t_ray *ray, t_object l, int i);
void		try_sphere(t_ray *ray, t_object obj, int i);
void		try_plan(t_ray *ray, t_object plan, int i);

/* ************************************************************************** */
/* vect_try_2.c                                                               */
/* ************************************************************************** */
void		try_cylinder(t_ray *ray, t_object obj, int i);

/* ************************************************************************** */
/* vect_utils.c                                                               */
/* ************************************************************************** */
t_vector	sous_vec_coord(t_coords a, t_coords b);
t_vector	add_vec_coord(t_coords a, t_coords b);
t_vector	sous_vec_vec(t_vector a, t_vector b);
t_vector	add_vec_vec(t_vector a, t_vector b);
t_coords	add_vec_coord_vec(t_coords a, t_vector b);

/* ************************************************************************** */
/* vect_utils_2.c                                                             */
/* ************************************************************************** */
t_vector	prod_vec_int(t_vector a, int k);
float		prod_scal_vec(t_vector a, t_vector b);
float		prod_scal_coord(t_coords a, t_coords b);
float		prod_scal_vec_coord(t_vector a, t_coords b);
t_vector	prod_vec_vec(t_vector a, t_vector b);

/* ************************************************************************** */
/* vect_utils_3.c                                                             */
/* ************************************************************************** */
t_vector	calc_ref_form(t_vector i, t_vector n);
float		magnitude(t_vector n);
float		magnitude_coord(t_coords n);
t_vector	normalise(t_vector n);
float		dist(t_coords a, t_coords b);

/* ************************************************************************** */
/* vect_utils_4.c                                                             */
/* ************************************************************************** */
t_coords	find_pos_touch(t_ray *ray, float t);
t_coords	give_coord(t_coords coord);
float		good_sol(float delta, float b, float a);
void		print_vec(t_vector vec);
void		print_coord(t_coords cor);

/* ************************************************************************** */
/* vect_utils_5.c                                                             */
/* ************************************************************************** */
/*
 * Function to return true if two vectors are the same, false otherwise.
 *
 * @param t_vector vector1	-> the first vector structure to compare
 * @param t_vector vector2	-> the second vector structure to compare
 * @return bool				-> the result of the comparison
 */
bool		is_vector_equal(t_vector vector1, t_vector vector2);

float		to_rad(float degree_angle);
t_vector	prod_vec_float(t_vector a, float k);

/* ************************************************************************** */
/* vect_utils_advance.c                                                       */
/* ************************************************************************** */
t_coords	advance_on_vec_z_inf(t_coords dep, t_vector dir, int k);
t_coords	advance_on_vec_z_sup(t_coords dep, t_vector dir, int k);
t_coords	advance_on_vec_z(t_coords dep, t_coords touch);
t_coords	advance_on_vec(t_coords dep, t_vector dir, int k);

#endif
