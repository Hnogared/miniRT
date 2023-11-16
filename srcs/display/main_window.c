/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 17:01:18 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ray_trace(t_data *data, int x, int y)
{
	int	color;

	color = *(int *)(unsigned char [4]){0, x * data->test, 
		(y * data->test) | (x * data->test), 0}; 
	return (color);
}

void	redraw_main_window(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 30 ;
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
	redraw_window(data->mlx_ptr, &data->main_window);
	mlx_string_put(data->mlx_ptr, data->main_window.ptr, 10, 20, 0xFFFFFF,
		"THIS IS A TEST TKT");
}
