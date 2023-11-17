/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 14:54:05 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_object	object;
	char		*line;
	char		**tab;
	t_data	prog_data;

	if (argc != 2)
		return (1);
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	check_scene(tab);

	ft_bzero(&prog_data, sizeof(t_data));
	prog_data.mlx_ptr = mlx_init();
	if (open_main_window(&prog_data, "miniRT"))
		return (2);
	free(line);
	free_str_tab(tab);
	prog_data.test = 10;
	redraw_main_window(&prog_data);
	init_key_hooks(&prog_data);
	mlx_loop(prog_data.mlx_ptr);
	free_data(&prog_data);

	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, (t_rgb_color){120, 40, 5});
	print_object_data(object);
	printf("la couleur en hexa vaut : %s\n", conv(object.special_data.sphere.color));

	// ft_bzero(&prog_data, sizeof(t_data));
	// prog_data.mlx_ptr = mlx_init();
	// if (open_main_window(&prog_data, "miniRT"))
	// 	return (1);
	// free(line);
	// free_str_tab(tab);
	// init_loops(&prog_data);
	// free_data(&prog_data);
	return (0);
}
