/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_conv_color_hexa.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/13 16:28:42 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdnoreturn.h>

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

int	key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		free_and_exit(data);
	return (0);
}

void	init_loops(t_data *data)
{
//	mlx_loop_hook(data->ptr, &disp_main_image, data);
	mlx_hook(data->main_window.ptr, KeyPress, KeyPressMask, &key_handler, data);
	mlx_hook(data->main_window.ptr, 17, 0, &free_and_exit, data);
	mlx_loop(data->mlx_ptr);
}

void	free_str_tab(char **str_tab)
{
	char	**temp;

	temp = str_tab;
	while (*temp)
		free(*(temp++));
	free(str_tab);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_object	object;
	// char		*line;
	// char		**tab;
	// t_data	prog_data;

	// if (argc != 2)
	// 	return (1);
	// check_file(argv[1]);
	// line = get_file(argv[1]);
	// tab = ft_split(line, '\n');
	// check_scene(tab);


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

