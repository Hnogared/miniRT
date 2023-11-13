/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/13 15:30:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdnoreturn.h>

/*
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
*/

void	free_data(t_data *data)
{
	my_destroy_window(data->mlx_ptr, &data->main_window);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

noreturn int	free_and_exit(t_data *data)
{
	free_data(data);
	exit(0);
}

void	init_loops(t_data *data)
{
//	mlx_loop_hook(data->ptr, &disp_main_image, data);
//	mlx_hook(data->win, KeyPress, KeyPressMask, &key_handler, data);
	mlx_hook(data->main_window.ptr, 17, 0, &free_and_exit, data);
	mlx_loop(data->mlx_ptr);
}

int	main(void)
{
	t_data	prog_data;

	prog_data.mlx_ptr = mlx_init();
	if (open_main_window(&prog_data, "miniRT"))
		return (1);
//	my_new_window(prog_data.mlx_ptr, &prog_data.main_window,
//		(int []){WIN_WIDTH, WIN_HEIGHT}, "Hello !");
	init_loops(&prog_data);
	free_data(&prog_data);
	return (0);
}

//	t_object	object;
//	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
//	set_object_color(&object, (t_rgb_color){110, 0, 5});
//	print_object_data(object);
//	printf("%f\n", object.special_data.sphere.diameter);
