/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:55:03 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/13 15:57:16 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to create and initialize a new t_image structure pointer.
 *
 * @param void *mlx_ptr			-> pointer to the image's mlx instance
 * @param t_image *new_img_p	-> pointer to image to create and initialize
 * @param int width				-> width of the new image
 * @param int height			-> height of the new image
 * @return t_image *			-> pointer to the newly initialized image
 */
t_image	*my_new_image(void *mlx_ptr, t_image *new_img_p, int width, int height)
{
	if (!new_img_p)
		return (NULL);
	new_img_p->ptr = mlx_new_image(mlx_ptr, width, height);
	if (!new_img_p->ptr)
		return (NULL);
	new_img_p->addr = mlx_get_data_addr(new_img_p->ptr,
			&new_img_p->bits_per_pixel, &new_img_p->line_size,
			&new_img_p->endian);
	new_img_p->width = width;
	new_img_p->height = height;
	return (new_img_p);
}

/*
 * Function to change an image's pixel color at the coordinates x and y.
 *
 * @param t_image *image	-> pointer to the image structure to modify
 * @param int x				-> x coordinate of the pixel to change
 * @param int y				-> y coordinate of the pixel to change
 * @param int color			-> the pixel's new color
 */
void	my_put_pixel_to_image(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + y * image->line_size + x * (image->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}
