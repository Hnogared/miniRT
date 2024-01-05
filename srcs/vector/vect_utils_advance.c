/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_advance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:12:02 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/05 15:12:03 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coords	advance_on_vec_z_inf(t_coords dep, t_vector dir, int k)
{
	t_coords	new;

	new.x = dep.x;
	new.y = dep.y;
	new.z = dep.z - k * dir.z;
	return (new);
}

t_coords	advance_on_vec_z_sup(t_coords dep, t_vector dir, int k)
{
	t_coords	new;

	new.x = dep.x;
	new.y = dep.y;
	new.z = dep.z + k * dir.z;
	return (new);
}

t_coords	advance_on_vec_z(t_coords dep, t_coords touch)
{
	t_coords	new;

	new.x = dep.x;
	new.y = dep.y;
	new.z = touch.z;
	return (new);
}

t_coords	advance_on_vec(t_coords dep, t_vector dir, int k)
{
	t_coords	new;

	new.x = dep.x + k * dir.x;
	new.y = dep.y + k * dir.y;
	new.z = dep.z + k * dir.z;
	return (new);
}
