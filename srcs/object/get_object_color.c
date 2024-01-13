/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:19:58 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 14:38:16 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the color of an object with no color attribute.
 *
 * @param[unused] t_special_data special_data	-> placeholder special data 
 * @return t_rgb_color							-> the default color structure
 */
t_rgb_color	get_uncolored_color(__attribute__((unused))
	t_special_data special_data)
{
	return ((t_rgb_color){0, 0, 0});
}

/*
 * Function to return the color of a sphere's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different object.
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
 * memory has been structured for a different object.
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
 * memory has been structured for a different object.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_cylinder_color(t_special_data special_data)
{
	return (special_data.cylinder.color);
}

/*
 * Function to return the color of a light's special data.
 * The returned color structure is undefined if the parameter special data
 * memory has been structured for a different object.
 *
 * @param t_special_data special_data	-> the special data to get the color from
 * @return t_rgb_color					-> the retrieved color structure
 */
t_rgb_color	get_light_color(t_special_data special_data)
{
	return (special_data.light.color);
}
