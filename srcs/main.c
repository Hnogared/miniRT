/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/04 15:20:37 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_rays(t_data *data)
{
	unsigned short	i;

	i = 0;
	while (i < data->obj_count)
	{
		print_object_data(data->scene_objects[i]);
		printf("\n");
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
	free_str_tab(tab);
	get_rays(&data);
	//print_vector(data.view_rays[0][0].vector);
	redraw_main_window(&data);
	//free(data->scene_objects);
	mlx_loop(data.mlx_ptr);
	return (0);
}
