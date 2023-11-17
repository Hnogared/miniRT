/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/17 17:36:28 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	object_a(char *s)
{		
	(void)s;
}

void	initialize_data(t_data *data, char **tab)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	ft_bzero(data, sizeof(t_data));
	while (tab[len])
		len++;
	data->scene_objects = (t_object *)malloc(sizeof(t_object) * len);	
	data->obj_count = len;
	if (tab[i])
	{
		if (tab[i][0] == 'A')
			object_a(tab[i]);
		i++;
	}
	free(data->scene_objects);
}

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;
	//t_object	object;
	t_data		prog_data;

	if (argc != 2)
		return (1);
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	check_scene(tab);
	initialize_data(&prog_data, tab);
	free(line);
	free_str_tab(tab);

	/*
	prog_data.mlx_ptr = mlx_init();
	if (open_main_window(&prog_data, "miniRT"))
		return (2);
	prog_data.test = 10;
	redraw_main_window(&prog_data);
	init_key_hooks(&prog_data);
	mlx_loop(prog_data.mlx_ptr);
	free_data(&prog_data);
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
