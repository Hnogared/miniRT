/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::     :::   */
/*   vector.h                                            :+:    :+:   :+:     */
/*                                                            +:+   +:+ +:+   */
/*   By: hnogared <hnogared@student.42perpignan.fr         +#+    +#+  +:+    */
/*                                                      +#+     +#+#+#+#+#+   */
/*   Created: 2024/01/09 03:04:55 by hnogared         #+#            #+#      */
/*   Updated: 2024/01/09 03:08:24 by hnogared       ########        ###.lol   */
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
 * @param float ro_matrix_to_set[3][3]	-> rotation matrix array to initialize
 * @param t_vector vector1				-> vector at the rotation start
 * @param t_vector vector2				-> vector at the rotation end
 */
void		get_rotation_matrix(float rot_matrix_to_set[3][3], t_vector vector1,
				t_vector vector2);

/* ************************************************************************** */
/* vect.c                                                                     */
/* ************************************************************************** */
int			do_touch(t_ray *ray, t_object obj, int i);
void		ray_advance(const t_data *data, t_ray *ray);

/* ************************************************************************** */
/* vect_add_subs.c                                                            */
/* ************************************************************************** */
/*
 * Function to return the substraction of two coords structures as a vector.
 *
 * @param t_coords a	-> coords structure from which to substract
 * @param t_coords b	-> coords structure to substract
 * @return t_vector		-> the vector resulting from the substraction
 */
t_vector	subs_vec_coords(t_coords a, t_coords b);

/*
 * Function to return the addition of two coords structures as a vector.
 *
 * @param t_coords a	-> coords structure to add to
 * @param t_coords b	-> coords structure to add
 * @return t_vector		-> the vector resulting from the addition
 */
t_vector	add_vec_coords(t_coords a, t_coords b);

/*
 * Function to return the substraction of two vector structures as a vector.
 *
 * @param t_vector a	-> vector structure from which to substract
 * @param t_vector b	-> vector structure to substract
 * @return t_vector		-> the vector resulting from the substraction
 */
t_vector	subs_vec_vec(t_vector a, t_vector b);

/*
 * Function to return the addition of two vector structures as a vector.
 *
 * @param t_vector a	-> vector structure to add to
 * @param t_vector b	-> vector structure to add
 * @return t_vector		-> the vector resulting from the addition
 */
t_vector	add_vec_vec(t_vector a, t_vector b);

/*
 * Function to return the addition of a coords structure and a vector structure
 * as a coords structure.
 *
 * @param t_coords a	-> coords structure to add to
 * @param t_vector b	-> vector structure to add
 * @return t_coords		-> the coords resulting from the addition
 */
t_coords	add_vec_coord_vec(t_coords a, t_vector b);

/* ************************************************************************** */
/* vect_calc.c                                                                */
/* ************************************************************************** */
/*
 * Function to calculate the vector resulting from the reflection of a ray on an
 * object.
 *
 * @param t_ray ray		-> the ray to reflect
 * @param t_object obj	-> the object structure to reflect onto
 * @return t_vector		-> the reflection vector
 *
 * @child_func sphere_ref			-> function to reflect a ray on a sphere
 * @child_func plane_ref			-> function to reflect a ray on a plane
 * @child_func cylinder_side_ref	-> function to reflect a ray on a cyl. side
 * @child_func cylinder_ext_ref		-> function to reflect a ray on a cyl. end
 */
t_vector	get_reflection_vector(t_ray ray, t_object obj);

/* ************************************************************************** */
/* vect_prod.c                                                                */
/* ************************************************************************** */
/*
 * Function to return the product of a vector structure and an integer.
 *
 * @param t_vector a	-> vector to multiply
 * @param int k			-> integer to multiply
 * @return t_vector		-> the vecotr resulting from the multiplication
 */
t_vector	prod_vec_int(t_vector a, int k);

/*
 * Function to return the scalar product of two vector structures.
 *
 * @param t_vector a	-> first vector of the product
 * @param t_vector b	-> second vector of the product
 * @return float		-> result of the scalar product
 */
float		prod_scal_vec(t_vector a, t_vector b);

/*
 * Function to return the scalar product of two coords structures.
 *
 * @param t_coords a	-> first coords of the product
 * @param t_coords b	-> second coords of the product
 * @return float		-> result of the scalar product
 */
float		prod_scal_coords(t_coords a, t_coords b);

/*
 * Function to return the scalar product of a vector structure and a coords
 * structure.
 *
 * @param t_vector a	-> vector structure as first factor of the product
 * @param t_coords b	-> coords structure as second factor of the product
 * @return float		-> result of the scalar product
 */
float		prod_scal_vec_coords(t_vector a, t_coords b);

/*
 * Function to return the cross product between two vector stuctures.
 *
 * @param t_vector a	-> vector structure as first factor of the product
 * @param t_coords b	-> coords structure as second factor of the product
 * @return t_vector		-> result of the cross product
 */
t_vector	prod_vec_vec(t_vector a, t_vector b);

/* ************************************************************************** */
/* vect_try.c                                                                 */
/* ************************************************************************** */
/*
 * Function to trace a ray, check if it touches a light object and update
 * it if true.
 *
 * @param t_ray *ray		-> pointer to the ray to test and update
 * @param t_object light	-> light object to check the collision with
 * @param int i				-> objects array index of the object structure
 */
void		try_light(t_ray *ray, t_object light, int i);

/*
 * Function to trace a ray, check if it touches a sphere object and update
 * it if true.
 *
 * @param t_ray *ray		-> pointer to the ray to test and update
 * @param t_object sphere	-> sphere object to check the collision with
 * @param int i				-> objects array index of the object structure
 */
void		try_sphere(t_ray *ray, t_object sphere, int i);

/*
 * Function to trace a ray, check if it touches a plane object and update
 * it if true.
 *
 * @param t_ray *ray		-> pointer to the ray to test and update
 * @param t_object plane	-> plane object to check the collision with
 * @param int i				-> objects array index of the object structure
 */
void		try_plane(t_ray *ray, t_object plane, int i);

/* ************************************************************************** */
/* vect_try_2.c                                                               */
/* ************************************************************************** */
/*
 * Function to trace a ray, check if it touches a cylinder object and update it
 * if true.
 *
 * @param t_ray *ray	-> pointer to the ray to test and update
 * @param t_object cyl	-> cylinder object to check the collision with
 * @param int i			-> objects array index of the object struct
 *
 * @child_func try_vertical_cylinder_side-> function to test the cylindrical side
 * @child_func try_cylinder_ext	-> function to test a [cy-ends]-ray collision
 */
void		try_cylinder(t_ray *ray, t_object cyl, int i);

/* ************************************************************************** */
/* vect_utils_3.c                                                             */
/* ************************************************************************** */
float		magnitude(t_vector n);
float		magnitude_coord(t_coords n);
float		dist(t_coords a, t_coords b);
t_vector	normalise(t_vector n);
t_vector	calc_ref_form(t_vector i, t_vector n);

/* ************************************************************************** */
/* vect_utils_4.c                                                             */
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
float		good_sol(float delta, float b, float a);
t_coords	find_pos_touch(t_ray *ray, float t);
t_vector	prod_vec_float(t_vector a, float k);

/* ************************************************************************** */
/* vect_utils_advance.c                                                       */
/* ************************************************************************** */
t_coords	advance_on_vec_z_inf(t_coords dep, t_vector dir, int k);
t_coords	advance_on_vec_z_sup(t_coords dep, t_vector dir, int k);
t_coords	advance_on_vec_z(t_coords dep, t_coords touch);
t_coords	advance_on_vec(t_coords dep, t_vector dir, int k);

#endif
