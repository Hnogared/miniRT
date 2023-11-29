/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/29 17:48:00 by hnogared         ###   ########.fr       */
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
	y = 30;
	while (y < data->main_window.height)
	{
		color = ray_trace(data, x, y);
		my_put_square_to_window(&data->main_window, (int [2]){x, y},
			(int [2]){data->main_window.pixel_ratio,
			data->main_window.pixel_ratio}, color);
		x += data->main_window.pixel_ratio;
		if (x < data->main_window.width)
			continue ;
		x = 0;
		y += data->main_window.pixel_ratio;
	}
	redraw_window(data->mlx_ptr, &data->main_window);
	mlx_string_put(data->mlx_ptr, data->main_window.ptr, 10, 20, 0xFFFFFF,
		"THIS IS A TEST TKT");
}
