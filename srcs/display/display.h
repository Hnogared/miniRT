/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:04:31 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 13:51:23 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

/* ************************************************************************** */
/* image_handling.c                                                           */
/* ************************************************************************** */
/*
 * Function to create and initialize a new t_image structure.
 *
 * @param void *mlx_ptr			-> pointer to the image's mlx instance
 * @param int width				-> width of the new image
 * @param int height			-> height of the new image
 * @return t_image				-> the newly created image
 */
t_image		my_new_image(void *mlx_ptr, int width, int height);

/*
 * Function to return the pixel color value of an image at x-y coordinates.
 *
 * @param t_image image	-> image structure to get the pixel color from
 * @param int x			-> x coordinate of the pixel to get
 * @param int y			-> y coordinate of the pixel to get
 * @return size_t		-> color value of the retrieved pixel
 */
size_t		get_image_pixel(t_image image, int x, int y);

/*
 * Function to change an image's pixel color at the coordinates x and y.
 *
 * @param t_image *image	-> pointer to the image structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param size_t color		-> the pixel's new color
 */
void		set_image_pixel(t_image *image, int x, int y, size_t color);

/* ************************************************************************** */
/* render_window.c                                                            */
/* ************************************************************************** */
/*
 * Function to open the program's render window (the main window).
 * The window will have the computer screen's width if WIN_WIDTH <= 0.
 * The window will have the comupter screen's height - 100 if WIN_HEIGHT <= 0.
 *
 * @param t_data *data	-> pointer to the program data
 * @param char *title	-> title of the window seen on the window bar
 * @return int			-> status code of the function
 */
int			open_render_window(t_data *data, char *title);

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
int			redraw_render_window(t_data *data);

/* ************************************************************************** */
/* rgb_color.c                                                                */
/* ************************************************************************** */
/*
 * Function to convert a t_rgb_color structure into an unsigned integer.
 *
 * @param t_rgb_color color	-> rgb color structure to convert
 * @return size_t			-> the corresponding unsigned int color
 */
size_t		rgb_to_sizet(t_rgb_color color);

/*
 * Function to add a proportion of an rgb color to another one.
 * This effectively brightens up the color that is being added onto.
 *
 * @param t_rgb_color start_color	-> color structure to add onto
 * @param t_rgb_color add_color		-> color structure to add to the first one
 * @param float ratio				-> proportion of the @param add_color to add
 * @return t_rgb_color				-> the addition's resulting rgb color
 */
t_rgb_color	rgb_color_lighten(t_rgb_color start_color, t_rgb_color add_color,
				float ratio);

/*
 * Function to mix/average out a proportion of an rgb color to another one.
 *
 * @param t_rgb_color start_color	-> color structure to mix with
 * @param t_rgb_color mix_color		-> color structure to mix with the first one
 * @param float ratio				-> proportion of the @param mix_color to mix
 * @return t_rgb_color				-> the mix resulting rgb color
 */
t_rgb_color	rgb_color_mix(t_rgb_color start_color, t_rgb_color mix_color,
				float ratio);

/* ************************************************************************** */
/* window_handling.c                                                          */
/* ************************************************************************** */
/*
 * Function to get the color of a window image's pixel at x-y coordinates.
 *
 * @param t_window window	-> window structure to get the pixel from
 * @param int x				-> x coordinate of the pixel to retrieve
 * @param int y				-> y coordinate of the pixel to retrieve
 * @return size_t			-> the retrieved pixel color
 */
size_t		get_window_pixel(t_window window, int x, int y);

/*
 * Function to get the color of a window's virtual pixel at the x-y
 * coordinates of the virtual pixels grid.
 *
 * @param t_window window	-> window structure to get the pixel from
 * @param int x				-> x coordinate of the virtual pixel to retrieve
 * @param int y				-> y coordinate of the virtual pixel to retrieve
 * @return size_t			-> the retrieved pixel color
 */
size_t		get_window_virtual_pixel(t_window window, int x, int y);

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
				char *title);

/*
 * Function to destroy a t_window structure pointer.
 *
 * @param void *mlx_ptr		-> pointer to the window's mlx instance
 * @param t_window *window	-> pointer to the window structure to destroy
 */
void		my_destroy_window(void *mlx_ptr, t_window *window);

/*
 * Function to redraw a window on the screen.
 *
 * @param void *mlx_ptr		-> pointer to the window's mlx instance
 * @param t_window *window	-> pointer to the window structure to redraw
 */
void		redraw_window(void *mlx_ptr, t_window *window);

/* ************************************************************************** */
/* window_modification.c                                                      */
/* ************************************************************************** */
/*
 * Function to change the pixel_ratio of a pointed t_window structure.
 * The parameter pointed window will be directly modified, the returned pointer
 * is not necessary for all cases.
 *
 * @param t_window *to_modify	-> pointer to the window to modify
 * @param int pixel_ratio		-> the pointed window's new pixel ratio to set
 * @return[redundant] t_window	-> instance of the newly modified window
 */
t_window	*set_window_pixel_ratio(t_window *to_modify, int pixel_ratio);

/*
 * Function to change the color of a window image's pixel at x-y coordinates.
 * /!\ This change can only be seen by calling redraw_window afterwards.
 *
 * @param t_window *window	-> pointer to the window structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param size_t color		-> the changed pixel's new color
 */
void		set_window_pixel(t_window *window, int x, int y, size_t color);

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
void		set_window_virtual_pixel(t_window *window, int x, int y,
				size_t color);

/*
 * Function to draw a colored square on a window image at x-y coordinates. 
 * /!\ This change can only be seen by calling redraw_window afterwards.
 *
 * @param t_window *window		-> pointer to the window structure to modify
 * @param int start_coords[2]	-> x-y coords of the square's top left corner
 * @param int size[2]			-> width and height of the square
 * @param size_t color			-> colorof the square
 */
void		put_square_to_window(t_window *window, int start_coords[2],
				int size[2], size_t color);

/*
 * Function to draw a colored percentage on the top left corner of a window.
 *
 * @param t_xvar *mlx_ptr	-> pointer to the mlx instance
 * @param t_window window	-> data of the window to draw the percentage on
 * @param int percentage	-> percentage to display
 * @param int color			-> color of the percentage to display
 */
void		put_percent_to_window(t_xvar *mlx_ptr, t_window window,
				int percentage, int color);

#endif
