/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:57:14 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 22:05:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

/* rotation.c */
t_basis		axial_basis_rotation(t_basis to_rotate, float angle, t_vector axis);
t_vector	axial_vector_rotation(t_vector to_rotate, float angle,
				t_vector axis);
t_vector	matrix_vector_rotation(t_vector to_rotate, float rot_matrix[3][3]);
t_coords	matrix_coords_rotation(t_coords to_rotate, float rot_matrix[3][3]);
void		get_rotation_matrix(float rot_matrix_to_set[3][3], t_vector vector1,
				t_vector vector2);

/* rotation_2.c */
float		to_rad(float degree_angle);
t_vector	prod_vec_float(t_vector a, float k);

/* vect.c */
int			do_touch(t_ray *ray, t_object obj, int i);
void		ray_advance(const t_data *data, t_ray *ray);

/* vect_calc.c */
t_vector	calcul_ref(const t_ray *ray, t_object obj, int res);

/* vect_try.c */
void		try_light(t_ray *ray, t_object l, int i);
void		try_sphere(t_ray *ray, t_object obj, int i);
void		try_plan(t_ray *ray, t_object plan, int i);

/* vect_try_2.c */
void		try_cylinder(t_ray *ray, t_object obj, int i);

/* vect_utils.c */
t_vector	sous_vec_coord(t_coords a, t_coords b);
t_vector	add_vec_coord(t_coords a, t_coords b);
t_vector	sous_vec_vec(t_vector a, t_vector b);
t_vector	add_vec_vec(t_vector a, t_vector b);
t_coords	add_vec_coord_vec(t_coords a, t_vector b);

/* vect_utils_2.c */
t_vector	prod_vec_int(t_vector a, int k);
float		prod_scal_vec(t_vector a, t_vector b);
float		prod_scal_coord(t_coords a, t_coords b);
float		prod_scal_vec_coord(t_vector a, t_coords b);
t_vector	prod_vec_vec(t_vector a, t_vector b);

/* vect_utils_3.c */
t_vector	calc_ref_form(t_vector i, t_vector n);
float		magnitude(t_vector n);
float		magnitude_coord(t_coords n);
t_vector	normalise(t_vector n);
float		dist(t_coords a, t_coords b);

/* vect_utils_4.c */
t_coords	find_pos_touch(t_ray *ray, float t);
t_coords	give_coord(t_coords coord);
float		good_sol(float delta, float b, float a);
void		print_vec(t_vector vec);
void		print_coord(t_coords cor);

/* vect_utils_5.c */
/*
 * Function to return true if two vectors are the same, false otherwise.
 *
 * @param t_vector vector1	-> the first vector structure to compare
 * @param t_vector vector2	-> the second vector structure to compare
 * @return bool				-> the result of the comparison
 */
bool	is_vector_equal(t_vector vector1, t_vector vector2);

float		to_rad(float degree_angle);
t_vector	prod_vec_float(t_vector a, float k);

/* vect_utils_advance.c */
t_coords	advance_on_vec_z_inf(t_coords dep, t_vector dir, int k);
t_coords	advance_on_vec_z_sup(t_coords dep, t_vector dir, int k);
t_coords	advance_on_vec_z(t_coords dep, t_coords touch);
t_coords	advance_on_vec(t_coords dep, t_vector dir, int k);

/* vect_try_2_utils.c */
//int 		test(t_ray aligned_ray, t_object obj);
//void		give_sol(t_ray	*aligned_ray, float	t, int i);
//t_ray		switch_rb(t_ray *ray, t_object obj);
//t_coords	switch_cb(t_object obj);

#endif
