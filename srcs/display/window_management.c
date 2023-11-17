/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:47:12 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 16:31:14 by motoko           ###   ########.fr       */
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
	int	win_size[2];

	mlx_get_screen_size(data->mlx_ptr, &win_size[0], &win_size[1]);
	win_size[1] -= 100;
	if (WIN_WIDTH > 0 && WIN_WIDTH < win_size[0])
		win_size[0] = WIN_WIDTH;
	if (WIN_HEIGHT > 0 && WIN_HEIGHT < win_size[1])
		win_size[1] = WIN_HEIGHT;
	data->main_window = my_new_window(data->mlx_ptr, win_size, title);
	return (data->main_window.ptr == NULL);
}

/*
 * Function to open and initialize a t_window structure.
 *
 * @param void *mlx_ptr			-> pointer to the window's mlx instance
 * @param int dimensions[2]		-> width and height array of the new window
 * @param char *title			-> title of the new window senn on the window bar
 * @return t_window				-> the newly created window structure
 */
t_window	my_new_window(void *mlx_ptr, int dimensions[2], char *title)
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
 * Function to change the color of a window pixel at the x and y coordinates.
 * /!\ This change will only be seen after calling redraw_window afterwards.
 *
 * @param t_window *window	-> pointer to the window structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param int color			-> the changed pixel's new color
 */
void	my_put_pixel_to_window(t_window *window, int x, int y, int color)
{
	if (window && window->image.ptr)
		my_put_pixel_to_image(&window->image, x, y, color);
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
