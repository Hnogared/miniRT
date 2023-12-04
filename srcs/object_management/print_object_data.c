/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:28:41 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/28 12:20:13 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to display a t_object object structure's data in the terminal.
 * The object's data_print_func pointer is needed to display its special data.
 *
 * @param t_object object	-> the object structure to display
 */
void	print_object_data(t_object object)
{
	ft_printf("[Object data]\nCoords :\n");
	print_coords(object.coords);
	printf("Orientation vector :\n");
	print_vector(object.orientation_vector);
	ft_printf("\n");
	object.data_print_func(object.special_data);
}

/*
 * Function to display a t_coords coordinates structure in the terminal.
 *
 * @param t_coords coords	-> coordinates structure to display
 */
void	print_coords(t_coords coords)
{
	printf("coords(%f,%f,%f)\n", coords.x, coords.y, coords.z);
}

/*
 * Function to display a t_vector vector structure in the terminal.
 *
 * @param t_vector vector	-> vector structure to display
 */
void	print_vector(t_vector vector)
{
	printf("vector(%f,%f,%f)\n", vector.x, vector.y, vector.z);
}

/*
 * Function to display a t_rgb_color color structure in the terminal.
 *
 * t_rgb_color color	-> rgb color structure t display
 */
void	print_rgb_color(t_rgb_color color)
{
	printf("(%d:%d:%d)", color.red, color.green, color.blue);
}
