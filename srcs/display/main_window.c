/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/09 18:33:27 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to open the program's main window.
 * The window will have the computer screen's width if WIN_WIDTH <= 0.
 * The window will have the comupter screen's height - 100 if WIN_HEIGHT <= 0.
 *
 * @param t_data *data	-> pointer to the program data
 * @param char *title	-> title of the window seen on the window bar
 * @return int			-> status code of the function
 */
int	open_main_window(t_data *data, char *title)
{
	int	pixel_ratio;
	int	win_size[2];

	mlx_get_screen_size(data->mlx_ptr, &win_size[0], &win_size[1]);
	win_size[1] -= 100;
	if (WIN_WIDTH > 0 && WIN_WIDTH < win_size[0])
		win_size[0] = WIN_WIDTH;
	if (WIN_HEIGHT > 0 && WIN_HEIGHT < win_size[1])
		win_size[1] = WIN_HEIGHT;
	pixel_ratio = DEFAULT_PIXEL_RATIO + (DEFAULT_PIXEL_RATIO <= 0);
	data->main_window = my_new_window(data->mlx_ptr, win_size, pixel_ratio,
			title);
	return (data->main_window.ptr == NULL);
}

int	redraw_main_window(t_data *data)
{
	int		x;
	int		y;
	bool	reset;
	size_t	color;

//	print_vector(data->view_rays[0][0].vector, NULL);
//	print_vector(data->view_rays[data->main_window.virtual_height - 1]
//		[data->main_window.virtual_width - 1].vector, NULL);
	x = 0;
	y = 0;
	reset = data->main_window.reset;
	while (y < data->main_window.virtual_height)
	{
		color = raytrace(data, data->view_rays[y][x]);
		if (reset == false)
		{
			color = sizet_color_mix(color,
					get_window_virtual_pixel(data->main_window, x, y), 0.5f);
		}
		set_window_virtual_pixel(&data->main_window, x, y, color);
		x++;
		if (x < data->main_window.virtual_width)
			continue ;
		x = 0;
		y++;
	}
	redraw_window(data->mlx_ptr, &data->main_window);
	mlx_string_put(data->mlx_ptr, data->main_window.ptr, 10, 20, 0xFFFFFF,
		"THIS IS A TEST TKT");
	data->main_window.reset = false;
	return (0);
}
