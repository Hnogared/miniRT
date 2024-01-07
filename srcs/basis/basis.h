/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:16:13 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 22:17:12 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIS_H
# define BASIS_H

/* orthonormal_basis.c */
t_basis		get_ortho_basis_from_x(t_vector xxx_orientation);
t_basis		get_ortho_basis_from_y(t_vector y_orientation);
t_basis		get_ortho_basis_from_z(t_vector z_orientation);

/* switch_basis.c */
t_ray		switch_ray_basis(t_ray to_rotate, t_basis new_basis,
				t_basis old_basis);
t_coords	switch_coords_basis(t_coords to_rotate, t_basis new_basis,
				t_basis old_basis);
t_vector	switch_vector_basis(t_vector to_rotate, t_basis new_basis,
				t_basis old_basis);

#endif
