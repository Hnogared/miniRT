/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/01 17:03:42 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_rays(t_data *data)
{
	unsigned short	i;

	i = 0;
	while (i < 3)
	{
		print_object_data(data->scene_objects[i]);
		printf("\n\n");
		i++;
	}
	i = 0;
	while (i < data->obj_count && data->scene_objects[i].type != CAMERA_OBJ)
		i++;
	if (i == data->obj_count)
		return ;
	data->view_rays = get_view_rays(data->main_window, data->scene_objects[i]);
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
	check_scene(&data, tab);

	initialize_data(&data, tab);
	free_str_tab(tab);

	get_rays(&data);
	print_vector(data.view_rays[0][0].vector);


	redraw_main_window(&data);
	mlx_loop(data.mlx_ptr);
	
	//redraw_main_window(&data);
	//mlx_loop(data.mlx_ptr);
	return (0);
}
