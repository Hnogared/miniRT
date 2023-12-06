/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:19:58 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/06 11:30:08 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb_color	get_uncolored_color(t_special_data special_data)
{
	(void)special_data;
	return ((t_rgb_color){0, 0, 0});
}

t_rgb_color	get_sphere_color(t_special_data special_data)
{
	return (special_data.sphere.color);
}

t_rgb_color	get_plane_color(t_special_data special_data)
{
	return (special_data.plane.color);
}

t_rgb_color	get_cylinder_color(t_special_data special_data)
{
	return (special_data.cylinder.color);
}
