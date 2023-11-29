/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/29 17:39:14 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vector_rotation_test(t_data *data)
{
	t_object	test;

	new_camera(&test, (t_coords){0, 0, 0}, 90);
	set_object_orientation(&test, (t_vector){0, 1, 0});
	camera_rays(data, test);
}

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
	check_scene(tab);

	//initialize_data(&data, tab);

	free_str_tab(tab);
	vector_rotation_test(&data);
	/*
	redraw_main_window(&prog_data);
	mlx_loop(prog_data.mlx_ptr);
	*/
	//redraw_main_window(&data);
	//mlx_loop(data.mlx_ptr);
	return (0);
}
