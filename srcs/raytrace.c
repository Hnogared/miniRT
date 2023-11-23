/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/21 11:54:30 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	camera_rays(t_data *data, t_object camera)
{
	t_ray	*rays_tab;

	rays_tab = (t_ray *) malloc((data->main_window.width
		* data->main_window.height / pixel_ratio) * sizeof(t_ray));
	free(rays_tab);
	return (0);
}
