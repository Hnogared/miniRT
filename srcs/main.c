/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/28 11:42:55 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	obj_a(t_data *data, char *s)
{		
	char	**args;
	char	**color;

	args = ft_split(s, ' ');
	data->ambient_l.ratio = 0.2;
	color = ft_split(args[2], ',');
	data->ambient_l.color = (t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]),
				ft_atoi(color[2])};
	free_str_tab(color);
	free_str_tab(args);
}

int	initialize_data(t_data *data, char **tab)
{
	int	i;
	int	len;
	int	pos;
	
	i = 0;
	len = 0;
	pos = 0;
	ft_bzero(data, sizeof(t_data));
	while (tab[len])
		len++;
	data->scene_objects = (t_object *)malloc(sizeof(t_object) * len);	
	if (!data->scene_objects)
		return (3);
	data->obj_count = len;
	while (tab[i])
	{
		if (tab[i][0] == 'A')
			obj_a(data, tab[i]);
		if (tab[i][0] == 'C')
			new_camera(&(data->scene_objects[pos++]), (t_coords){-50, 0, 20}, 70);
		if (tab[i][0] == 'L')
		{
			new_light(&(data->scene_objects[pos++]), (t_coords){-50, 0, 20}, 0.7);
			//set_object_color();
		}
		i++;
	}
	data->mlx_ptr = mlx_init();
	if (open_main_window(data, "miniRT"))
		return (2);
	data->test = 10;
	data->pixel_ratio = DEFAULT_PIXEL_RATIO + (DEFAULT_PIXEL_RATIO <= 0);
	free(data->scene_objects);
	init_key_hooks(data);
	return (0);
}

void	vector_rotation_test(t_data *data)
{
	t_object	test;

	new_camera(&test, (t_coords){0, 0, 0}, 90);
	printf("\n");
	set_object_orientation(&test, (t_vector){0, 1, 0});
	print_vector(test.loc_basis.x);
	print_vector(test.loc_basis.y);
	print_vector(test.loc_basis.z);
	camera_rays(data, test);
}

int	main(int argc, char **argv)
{
	
	char		*line;
	char		**tab;
	//t_object	object;
	t_data		prog_data;

	init_error_tab(prog_data.error_tab);
	if (argc != 2)
		return (ft_perror(NULL, prog_data.error_tab, RTERR_ARGS_COUNT));
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	free(line);
	check_scene(tab);
	initialize_data(&prog_data, tab);
	free_str_tab(tab);
	vector_rotation_test(&prog_data);
	/*
	redraw_main_window(&prog_data);
	mlx_loop(prog_data.mlx_ptr);
	*/
	/*
	new_sphere(&object, (t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, (t_rgb_color){120, 40, 5});
	print_object_data(object);
	//object.data_print_func(special_data);
	printf("la couleur en hexa vaut : %s\n", conv(object.special_data.sphere.color));
	*/
	return (0);
}
