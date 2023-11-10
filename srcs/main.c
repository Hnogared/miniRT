/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 17:31:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_object	object;
	t_coords	coords;
	t_rgb_color	color;

	if (argc == 2)
		check_file(argv[1]);
	coords.x = 1;
	coords.y = 0;
	coords.z = 10;
	color.red = 110;
	color.green = 0;
	color.blue = 5;
	new_sphere(&object, &coords, 1.0);
	set_object_color(&object, &color);
	print_object_data(object);
	return (0);
}
