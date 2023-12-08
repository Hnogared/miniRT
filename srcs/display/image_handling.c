/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:55:03 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/08 10:57:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to create and initialize a new t_image structure.
 *
 * @param void *mlx_ptr			-> pointer to the image's mlx instance
 * @param int width				-> width of the new image
 * @param int height			-> height of the new image
 * @return t_image				-> the newly created image
 */
t_image	my_new_image(void *mlx_ptr, int width, int height)
{
	t_image	image;

	image.ptr = NULL;
	if (!mlx_ptr)
		return (image);
	image.ptr = mlx_new_image(mlx_ptr, width, height);
	if (!image.ptr)
		return (image);
	image.addr = mlx_get_data_addr(image.ptr, &image.bits_per_pixel,
			&image.line_size, &image.endian);
	image.width = width;
	image.height = height;
	return (image);
}

/*
 * Function to return the pixel color value of an image at x-y coordinates.
 *
 * @param t_image image	-> image structure to get the pixel color from
 * @param int x			-> x coordinate of the pixel to get
 * @param int y			-> y coordinate of the pixel to get
 * @return size_t		-> color value of the retrieved pixel
 */
size_t	get_image_pixel(t_image image, int x, int y)
{
	return (*(size_t *) image.addr + (y * image.line_size
			+ x * image.bits_per_pixel / 8));
}

/*
 * Function to change an image's pixel color at the coordinates x and y.
 *
 * @param t_image *image	-> pointer to the image structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param size_t color		-> the pixel's new color
 */
void	set_image_pixel(t_image *image, int x, int y, size_t color)
{
	char	*dst;

	dst = image->addr + (y * image->line_size + x * image->bits_per_pixel / 8);
	*(size_t *)dst = color;
}
