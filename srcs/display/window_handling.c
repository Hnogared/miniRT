/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:47:12 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 17:11:23 by hnogared         ###   ########.fr       */
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
 * Function to open and initialize a t_window structure.
 *
 * @param void *mlx_ptr			-> pointer to the window's mlx instance
 * @param int dimensions[2]		-> width and height array of the new window
 * @param int pixel_ratio		-> virtual pixel size (h & w) for each ray traced
 * @param char *title			-> title of the new window senn on the window bar
 * @return t_window				-> the newly created window structure
 */
t_window	my_new_window(void *mlx_ptr, int dimensions[2], int pixel_ratio,
	char *title)
{
	t_window	window;

	window.ptr = NULL;
	if (!mlx_ptr || !dimensions || !title)
		return (window);
	window.ptr = mlx_new_window(mlx_ptr, dimensions[0], dimensions[1], title);
	if (!window.ptr)
		return (window);
	window.image = my_new_image(mlx_ptr, dimensions[0], dimensions[1]);
	if (!window.image.ptr)
	{
		mlx_destroy_window(mlx_ptr, window.ptr);
		window.ptr = NULL;
		return (window);
	}
	window.width = dimensions[0];
	window.height = dimensions[1];
	set_window_pixel_ratio(&window, pixel_ratio);
	window.draw_pos[0] = 0;
	window.draw_pos[1] = 0;
	return (window);
}

/*
 * Function to destroy a t_window structure pointer.
 *
 * @param void *mlx_ptr		-> pointer to the window's mlx instance
 * @param t_window *window	-> pointer to the window structure to destroy
 */
void	my_destroy_window(void *mlx_ptr, t_window *window)
{
	if (!mlx_ptr || !window)
		return ;
	mlx_destroy_window(mlx_ptr, window->ptr);
	window->ptr = NULL;
	mlx_destroy_image(mlx_ptr, window->image.ptr);
}

/*
 * Function to redraw a window on the screen.
 *
 * @param void *mlx_ptr		-> pointer to the window's mlx instance
 * @param t_window *window	-> pointer to the window structure to redraw
 */
void	redraw_window(void *mlx_ptr, t_window *window)
{
	mlx_put_image_to_window(mlx_ptr, window->ptr, window->image.ptr, 0, 0);
}
