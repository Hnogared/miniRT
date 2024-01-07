/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:16:13 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 13:43:52 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIS_H
# define BASIS_H

/* ************************************************************************** */
/* orthonormal_basis.c                                                        */
/* ************************************************************************** */
/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the x axis.
 *
 * @param t_vector xxx_orientation	-> the new basis' x axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
t_basis		get_ortho_basis_from_x(t_vector xxx_orientation);

/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the y axis.
 *
 * @param t_vector xxx_orientation	-> the new basis' y axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
t_basis		get_ortho_basis_from_y(t_vector y_orientation);

/*
 * Function to calculate a 3D right-handed basis' orthogonal normal/unit vectors
 * with the @param vector as the z axis.
 *
 * @param t_vector z_orientation	-> the new basis' z axis orientation
 * @return t_basis					-> the newly calculated orthogonal basis
 */
t_basis		get_ortho_basis_from_z(t_vector z_orientation);

/* ************************************************************************** */
/* switch_basis.c                                                             */
/* ************************************************************************** */
/*
 * Function to transpose a t_ray structure from one basis to another.
 * If the bases are the same, return the original ray.
 *
 * @param t_ray to_rotate	-> ray structure to modify for the transposition
 * @param t_basis new_basis	-> the basis into which the ray is converted
 * @param t_basis old_basis	-> the basis from which the ray is converted
 * @return t_ray			-> the new transposed ray
 */
t_ray		switch_ray_basis(t_ray to_rotate, t_basis new_basis,
				t_basis old_basis);

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
				t_basis old_basis);

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
				t_basis old_basis);

#endif
