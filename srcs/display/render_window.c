/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/04 22:17:49 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to open the program's render window (the main window).
 * The window will have the computer screen's width if WIN_WIDTH <= 0.
 * The window will have the comupter screen's height - 100 if WIN_HEIGHT <= 0.
 *
 * @param t_data *data	-> pointer to the program data
 * @param char *title	-> title of the window seen on the window bar
 * @return int			-> status code of the function
 */
int	open_render_window(t_data *data, char *title)
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
	data->render_window = my_new_window(data->mlx_ptr, win_size, pixel_ratio,
			title);
	return (data->render_window.ptr == NULL);
}

/*
 * Function to build and redraw the window displaying the raytracing results.
 * The function is called at each mlx loop iteration to allow for the
 * interuption of the render window redrawing at an mlx event (e.g a keypress).
 * Each function call executes the raytracing to be stored in the next
 * uncalculated pixel of the window.
 * While building, the window redraws and a progress percentage is displayed on
 * the top left corner at each built virtual pixels line.
 * Returns immediately if the window is fully drawn.
 *
 * @param t_data *data		-> the program data containing the render window
 * @[redundant]return int	-> 0 all the time
 */
int	redraw_render_window(t_data *data)
{
	int			x;
	int			y;
	size_t		color;
	t_window	*render_window;

	render_window = &data->render_window;
	if (render_window->draw_pos[0] >= render_window->virtual_width
		&& render_window->draw_pos[1] >= render_window->virtual_height)
		return (0);
	x = render_window->draw_pos[0];
	y = render_window->draw_pos[1];
	color = raytrace(data, data->view_rays[y][x], data->anti_aliasing);
	set_window_virtual_pixel(render_window, x, y, color);
	if (++x >= render_window->virtual_width)
	{
		redraw_window(data->mlx_ptr, render_window);
		put_percent_to_window(data->mlx_ptr, *render_window,
			++y * 100 / render_window->virtual_height, 0xFF0000);
		if (y >= render_window->virtual_height)
			return (0);
		x = 0;
	}
	render_window->draw_pos[0] = x;
	render_window->draw_pos[1] = y;
	return (0);
}
