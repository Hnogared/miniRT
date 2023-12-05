/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:28:41 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/05 11:20:10 by hnogared         ###   ########.fr       */
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
	object.data_print_func(object.special_data);
	printf("[Object data]\n");
	print_coords(object.coords, NULL);
	print_vector(object.orientation_vector, NULL);
	print_basis(object.local_basis, NULL);
	printf("\n");
}

/*
 * Function to display a t_coords coordinates structure in the terminal.
 *
 * @param t_coords coords	-> coordinates structure to display
 * @param char *name		-> name of the coordinates displayed
 */
void	print_coords(t_coords coords, char *name)
{
	name = (char *)((uintptr_t) name + (uintptr_t) "Coords" * (!name));
	printf("%s : (%f,%f,%f)\n", name, coords.x, coords.y, coords.z);
}

/*
 * Function to display a t_vector vector structure in the terminal.
 *
 * @param t_vector vector	-> vector structure to display
 * @param char *name		-> name of the vector displayed
 */
void	print_vector(t_vector vector, char *name)
{
	name = (char *)((uintptr_t) name + (uintptr_t) "Vector" * (!name));
	printf("%s : (%f,%f,%f)\n", name, vector.x, vector.y, vector.z);
}

/*
 * Function to display a t_rgb_color color structure in the terminal.
 *
 * @param t_rgb_color color	-> rgb color structure to display
 * @param char *name		-> name of the color displayed
 */
void	print_rgb_color(t_rgb_color color, char *name)
{
	name = (char *)((uintptr_t) name + (uintptr_t) "Color" * (!name));
	printf("%s : (%d:%d:%d)\n", name, color.red, color.green, color.blue);
}

/*
 * Function to display a t_basis basis structure in the terminal.
 *
 * @param t_basis basis	-> basis structure to display
 * @param char *name	-> name of the basis displayed
 */
void	print_basis(t_basis basis, char *name)
{
	name = (char *)((uintptr_t) name + (uintptr_t) "Basis" * (!name));
	printf("%s : ", name);
	print_vector(basis.x, "x");
	printf("        ");
	print_vector(basis.y, "y");
	printf("        ");
	print_vector(basis.z, "z");
}
