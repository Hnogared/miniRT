/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_modification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:55:33 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 17:48:36 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to change the pixel_ratio of a pointed t_window structure.
 * The parameter pointed window will be directly modified, the returned pointer
 * is not necessary for all cases.
 *
 * @param t_window *to_modify	-> pointer to the window to modify
 * @param int pixel_ratio		-> the pointed window's new pixel ratio to set
 * @return[redundant] t_window	-> instance of the newly modified window
 */
t_window	*set_window_pixel_ratio(t_window *to_modify, int pixel_ratio)
{
	if (!to_modify || pixel_ratio <= 0)
		return (NULL);
	to_modify->pixel_ratio = pixel_ratio;
	to_modify->virtual_width = to_modify->width / pixel_ratio;
	to_modify->virtual_height = to_modify->height / pixel_ratio;
	return (to_modify);
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

/*
 * TODO comment
 */
void	put_percent_to_window(t_xvar *mlx_ptr, t_window window, int percentage,
	int color)
{
	int		i;
	char	percentage_str[5];
	char	*itoa_res;

	percentage = percentage * (percentage >= 0 && percentage <= 100);
	itoa_res = ft_itoa(percentage);
	if (!itoa_res)
		return ;
	i = -1;
	while (itoa_res[++i])
		percentage_str[i] = itoa_res[i];
	free(itoa_res);
	percentage_str[i++] = '%';
	percentage_str[i] = 0;
	mlx_string_put(mlx_ptr, window.ptr, 10, 20, color, percentage_str);
}
