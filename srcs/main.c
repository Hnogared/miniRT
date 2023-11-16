/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 11:04:07 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
/*	t_image	image;
	void	*mlx_ptr;
	
	mlx_ptr = mlx_init();
	image = my_new_image(mlx_ptr, 20, 20);
	my_put_pixel_to_image(&image, 1, 1, 0xFFFFFF);
	(void)argv;
	if (argc)
		return (0);
	return (0);
*/	char	*line;
	char	**tab;
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
	init_key_hooks(&prog_data);
	mlx_loop(prog_data.mlx_ptr);
	free_data(&prog_data);
	return (0);

}

//	t_object	object;
//	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
//	set_object_color(&object, (t_rgb_color){110, 0, 5});
//	print_object_data(object);
//	printf("%f\n", object.special_data.sphere.diameter);
