/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/04 14:00:52 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vector_rotation_test(void)
{
	float		rot_matrix[3][3];
	t_vector	start_vec;
	t_vector	axis;
	t_vector	rotated;
	t_object	test;

	start_vec = (t_vector){1, 0, 0};
	axis = (t_vector){0, 0, 1};
	print_vector(start_vec);
	printf("\n");
	rotated = axial_vector_rotation(start_vec, 90, axis);
	print_vector(rotated);
	get_rotation_matrix(rot_matrix, axis, rotated);
	print_vector(matrix_vector_rotation(axis, rot_matrix));
	new_camera(&test, (t_coords){0, 0, 0}, 10);
	printf("\n");
	set_object_orientation(&test, (t_vector){0, 0, 1});
	print_vector(test.local_axes.x);
	print_vector(test.local_axes.y);
	print_vector(test.local_axes.z);
}

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;
	t_object	object;
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

	free_str_tab(tab);
	return (0);
}
