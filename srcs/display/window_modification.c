/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:55:33 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/08 16:52:25 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to get the color of a window image's pixel at x-y coordinates.
 *
 * @param t_window window	-> window structure to get the pixel from
 * @param int x				-> x coordinate of the pixel to retrieve
 * @param int y				-> y coordinate of the pixel to retrieve
 * @return size_t			-> the retrieved pixel color
 */
size_t	get_window_pixel(t_window window, int x, int y)
{
	return (get_image_pixel(window.image, x, y));
}

/*
 * Function to get the color of a window's virtual pixel at the x-y
 * coordinates of the virtual pixels grid.
 *
 * @param t_window window	-> window structure to get the pixel from
 * @param int x				-> x coordinate of the virtual pixel to retrieve
 * @param int y				-> y coordinate of the virtual pixel to retrieve
 * @return size_t			-> the retrieved pixel color
 */
size_t	get_window_virtual_pixel(t_window window, int x, int y)
{
	int	virtual_x;
	int	virtual_y;

	virtual_x = x * window.pixel_ratio;
	virtual_y = y * window.pixel_ratio;
	return (get_window_pixel(window, virtual_x, virtual_y));
}

/*
 * Function to change the color of a window image's pixel at x-y coordinates.
 * /!\ This change can only be seen by calling redraw_window afterwards.
 *
 * @param t_window *window	-> pointer to the window structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param size_t color		-> the changed pixel's new color
 */
void	set_window_pixel(t_window *window, int x, int y, size_t color)
{
	set_image_pixel(&window->image, x, y, color);
}

/*
 * Function to change the color of a window's virtual pixel at the x-y
 * coordinates of the virtual pixels grid.
 * /!\ This change can only be seen by calling redraw_window afterwards.
 *
 * @param t_window *window	-> pointer to the window structure to modify
 * @param int x				-> x coordinate of the virtual pixel to change
 * @param int y				-> y coordinate of the virtual pixel to change
 * @param size_t color		-> the changed pixel's new color
 */
void	set_window_virtual_pixel(t_window *window, int x, int y, size_t color)
{
	int	*v_coords;
	int	*pixel_size;

	v_coords = (int [2]){x * window->pixel_ratio, y * window->pixel_ratio};
	pixel_size = (int [2]){window->pixel_ratio, window->pixel_ratio};
	put_square_to_window(window, v_coords, pixel_size, color);
}

/*
 * Function to draw a colored square on a window image at x-y coordinates. 
 * /!\ This change can only be seen by calling redraw_window afterwards.
 *
 * @param t_window *window		-> pointer to the window structure to modify
 * @param int start_coords[2]	-> x-y coords of the square's top left corner
 * @param int size[2]			-> width and height of the square
 * @param size_t color			-> colorof the square
 */
void	put_square_to_window(t_window *window, int start_coords[2], int size[2],
	size_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < size[1] && start_coords[1] + y <= window->height)
	{
		set_window_pixel(window, start_coords[0] + x, start_coords[1] + y,
			color);
		x++;
		if (x < size[0] && start_coords[0] + x <= window->width)
			continue ;
		x = 0;
		y++;
	}
}
