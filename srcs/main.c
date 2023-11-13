/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/13 13:01:09 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;

	if (argc != 2)
		return (0);
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	check_scene(tab);
	return (0);
}

//	t_object	object;
//	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
//	set_object_color(&object, (t_rgb_color){110, 0, 5});
//	print_object_data(object);
//	printf("%f\n", object.special_data.sphere.diameter);
