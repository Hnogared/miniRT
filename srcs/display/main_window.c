/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 18:01:55 by hnogared         ###   ########.fr       */
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


// TODO comment
int	redraw_main_window(t_data *data)
{
	int			x;
	int			y;
	size_t		color;
	t_window	*main_window;

	main_window = &data->main_window;
	if (main_window->draw_pos[0] >= main_window->virtual_width
		&& main_window->draw_pos[1] >= main_window->virtual_height)
		return (0);
	x = main_window->draw_pos[0];
	y = main_window->draw_pos[1];
	color = raytrace(data, data->view_rays[y][x], data->anti_aliasing);
	set_window_virtual_pixel(main_window, x, y, color);
	if (++x >= main_window->virtual_width)
	{
		redraw_window(data->mlx_ptr, main_window);
		put_percent_to_window(data->mlx_ptr, *main_window,
			++y * 100 / main_window->virtual_height, 0xFF0000);
		if (y >= main_window->virtual_height)
			return (0);
		x = 0;
	}
	main_window->draw_pos[0] = x;
	main_window->draw_pos[1] = y;
	return (0);
}
