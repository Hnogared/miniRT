/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/13 23:29:34 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_main_view_rays(t_data *data, bool needs_alloc)
{
	int	status;

	status = set_view_rays(&data->view_rays, data->main_window,
			*(data->active_camera), needs_alloc);
	if (status != 0)
	{
		status = ft_perror(NULL, data->error_tab, status);
		free_data(data);
		exit(status);
	}
}

int	initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (open_main_window(data, "miniRT"))
		return (2);
	init_key_hooks(data);
	return (0);
}


static void	print_scene_objects(unsigned short obj_count, t_object *scene_objects)
{
	while (obj_count--)
		print_object_data(scene_objects[obj_count]);
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
	print_scene_objects(data.obj_count, data.scene_objects);
	initialize_mlx(&data);
	free_str_tab(tab);
	get_main_view_rays(&data, true);
	redraw_main_window(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
