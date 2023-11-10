/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 18:03:18 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_object	object;

	if (argc == 2)
		check_file(argv[1]);
	new_sphere(&object, &(t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, &(t_rgb_color){110, 0, 5});
	print_object_data(object);
	return (0);
}
