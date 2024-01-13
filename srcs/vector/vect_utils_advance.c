/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils_advance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:12:02 by tlorne            #+#    #+#             */
/*   Updated: 2024/01/13 13:26:08 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the z axis shifted coordinates by following the oppsite
 * direction of a vector for a given distance.
 *
 * @param t_coords origin	-> coords to start shifting from
 * @param t_vector dir		-> direction vector to follow for the shift
 * @param int distance		-> distance to shift for
 * @return t_coords			-> the coordinates resulting from the shift
 */
t_coords	advance_on_vec_z_inf(t_coords origin, t_vector dir, int distance)
{
	t_coords	new;

	new.x = origin.x;
	new.y = origin.y;
	new.z = origin.z - distance * dir.z;
	return (new);
}

/*
 * Function to return the z axis shifted coordinates by following the direction
 * of a vector for a given distance.
 *
 * @param t_coords origin	-> coords to start shifting from
 * @param t_vector dir		-> direction vector to follow for the shift
 * @param int distance		-> distance to shift for
 * @return t_coords			-> the coordinates resulting from the shift
 */
t_coords	advance_on_vec_z_sup(t_coords origin, t_vector dir, int distance)
{
	t_coords	new;

	new.x = origin.x;
	new.y = origin.y;
	new.z = origin.z + distance * dir.z;
	return (new);
}

/*
 * Function to set the z coordinate of a coords structure to the one of a
 * different coords structure and return the result.
 *
 * @param t_coords origin	-> coords stucture for which to change the z coord
 * @param t_coords touch	-> coords structure from which to get the z coord
 * @return t_coords			-> the resulting coordinates
 */
t_coords	advance_on_vec_z(t_coords origin, t_coords touch)
{
	t_coords	new;

	new.x = origin.x;
	new.y = origin.y;
	new.z = touch.z;
	return (new);
}

/*
 * Function to return the shifted coordinates by following the direction of a
 * vector for a given distance.
 *
 * @param t_coords origin	-> coords to start shifting from
 * @param t_vector dir		-> direction vector to follow for the shift
 * @param int distance		-> distance to shift for
 * @return t_coords			-> the coordinates resulting from the shift
 */
t_coords	advance_on_vec(t_coords origin, t_vector dir, int distance)
{
	t_coords	new;

	new.x = origin.x + distance * dir.x;
	new.y = origin.y + distance * dir.y;
	new.z = origin.z + distance * dir.z;
	return (new);
}
