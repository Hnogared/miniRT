/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 11:51:33 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ray_trace(t_data *data, int x, int y)
{
	int	color;

	color = 0 | (unsigned char) y << 16 | (unsigned char) x << 16 | (unsigned char) x << 8;
	if (data)
		return (color);
	return (color);
}

void	redraw_main_window(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	while (y < data->main_window.height)
	{
		color = ray_trace(data, x, y);
		my_put_pixel_to_window(&data->main_window, x, y, color);
		x++;
		if (x < data->main_window.width)
			continue ;
		x = 0;
		y++;
	}
	mlx_string_put(data->mlx_ptr, data->main_window.ptr, 0, 0, 0xFF0000,
		"THIS IS A TEST TKT");
	redraw_window(data->mlx_ptr, &data->main_window);
}
