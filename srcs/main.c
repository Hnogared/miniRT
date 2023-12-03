/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/03 16:07:28 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;
	//t_object	object;
	t_data		data;
	int			status;

	status = 0;
	init_error_tab(data.error_tab);
	if (argc != 2)
		return (ft_perror(NULL, data.error_tab, RTERR_ARGS_COUNT));
	if (check_file(argv[1]) == -1)
		return (ft_perror(NULL, data.error_tab, RTERR_FILE_NAME));
	line = get_file(&data, argv[1]);
	tab = ft_split(line, '\n');
	free(line);
	status = check_scene(&data, tab);
	if (status)
	{
		free_str_tab(tab);
		return (status);
	}
	initialize_object(&data, tab);
	initialize_mlx(&data);

	//redraw_main_window(&data);
	//mlx_loop(data.mlx_ptr);

	/*
	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, (t_rgb_color){120, 40, 5});
	print_object_data(object);
	//object.data_print_func(special_data);
	printf("la couleur en hexa vaut : %s\n", conv(object.special_data.sphere.color)); */
	return (0);
}
