/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:47:12 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/07 10:52:41 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	window.pixel_ratio = pixel_ratio;
	window.virtual_width = window.width / pixel_ratio;
	window.virtual_height = window.height / pixel_ratio;
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
 * Function to change the color of a window image's pixel at x-y coordinates.
 * /!\ This change will only be seen after calling redraw_window afterwards.
 *
 * @param t_window *window	-> pointer to the window structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param size_t color		-> the changed pixel's new color
 */
void	my_put_pixel_to_window(t_window *window, int x, int y, size_t color)
{
	if (window && window->image.ptr)
		my_put_pixel_to_image(&window->image, x, y, color);
}

/*
 * Function to draw a colored square on a window image at x-y coordinates. 
 * /!\ This change will only be seen after calling redraw_window afterwards.
 *
 * @param t_window *window		-> pointer to the window structure to modify
 * @param int start_coords[2]	-> x-y coords of the square's top left corner
 * @param int size[2]			-> width and height of the square
 * @param size_t color			-> colorof the square
 */
void	my_put_square_to_window(t_window *window, int start_coords[2],
	int size[2], size_t color)
{
	int	x;
	int	y;

	if (!window || !window->image.ptr)
		return ;
	x = 0;
	y = 0;
	while (y < size[1] && start_coords[1] + y <= window->height)
	{
		my_put_pixel_to_window(window, start_coords[0] + x, start_coords[1] + y,
			color);
		x++;
		if (x < size[0] && start_coords[0] + x <= window->width)
			continue ;
		x = 0;
		y++;
	}
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
