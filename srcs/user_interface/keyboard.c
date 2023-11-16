/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 11:04:47 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_screen(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 1;
	y = 1;
	color = 0xFFFFFF;
	while (y < data->main_window.height)
	{
		my_put_pixel_to_window(&data->main_window, x, y, color);
		x++;
		if (x < data->main_window.width)
			continue ;
		x = 0;
		y++;
	}
	redraw_window(data->mlx_ptr, &data->main_window);
}

int	key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		free_and_exit(data);
	draw_screen(data);
	return (0);
}

void	init_key_hooks(t_data *data)
{
//	mlx_loop_hook(data->ptr, &disp_main_image, data);
	mlx_hook(data->main_window.ptr, KeyPress, KeyPressMask, &key_handler, data);
	mlx_hook(data->main_window.ptr, DestroyNotify, NoEventMask, &free_and_exit,
		data);
}
