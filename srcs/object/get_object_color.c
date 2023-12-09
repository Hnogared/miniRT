/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:19:58 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/09 19:35:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the color of a sphere's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different shape.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_sphere_color(t_special_data special_data)
{
	return (special_data.sphere.color);
}

/*
 * Function to return the color of a plane's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different shape.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_plane_color(t_special_data special_data)
{
	return (special_data.plane.color);
}

/*
 * Function to return the color of a cylinder's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different shape.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_cylinder_color(t_special_data special_data)
{
	return (special_data.cylinder.color);
}

/*
 * Function to return the color of an object with no color attribute.
 *
 * @[unused]param t_special_data special_data	-> placeholder special data 
 * @return t_rgb_color							-> the default color structure
 */
t_rgb_color	get_uncolored_color(t_special_data special_data)
{
	(void)special_data;
	return ((t_rgb_color){0, 0, 0});
}
