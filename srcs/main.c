/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/17 17:30:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	initialize_data(t_data *data, char **tab)
{
	int	i;
	
	ft_bzero(data, sizeof(t_data));
	i = 0;
	while (tab[i])
		i++;
	data->scene_objects = (t_object *)malloc(sizeof(t_object) * i);	
	if (!data->scene_objects)
		return (3);
	data->mlx_ptr = mlx_init();
	if (open_main_window(data, "miniRT"))
		return (2);
	data->test = 10;
	data->pixel_ratio = DEFAULT_PIXEL_RATIO + (DEFAULT_PIXEL_RATIO <= 0);
	return (0);
}

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;
	t_object	object;
	t_data		prog_data;

	if (argc != 2)
		return (1);
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	free(line);
	check_scene(tab);
	initialize_data(&prog_data, tab);
	free_str_tab(tab);

	redraw_main_window(&prog_data);
	init_key_hooks(&prog_data);
	mlx_loop(prog_data.mlx_ptr);
	free_data(&prog_data);

	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, (t_rgb_color){120, 40, 5});
	print_object_data(object);
	//object.data_print_func(special_data);
	printf("la couleur en hexa vaut : %s\n", conv(object.special_data.sphere.color));
	return (0);
}

