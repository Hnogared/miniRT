/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/29 17:14:36 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;
	//t_object	object;
	t_data		data;

	init_error_tab(data.error_tab);
	if (argc != 2)
		return (ft_perror(NULL, data.error_tab, RTERR_ARGS_COUNT));
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	free(line);
	check_scene(&data, tab);

	//initialize_data(&data, tab);

	free_str_tab(tab);
	//redraw_main_window(&data);
	//mlx_loop(data.mlx_ptr);

	/*
	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, (t_rgb_color){120, 40, 5});
	print_object_data(object);
	//object.data_print_func(special_data);
	printf("la couleur en hexa vaut : %s\n", conv(object.special_data.sphere.color));
	*/
	return (0);
}
