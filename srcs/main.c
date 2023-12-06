/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/06 18:29:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_main_view_rays(t_data *data, bool needs_alloc)
{
	unsigned short	i;

	i = 0;
	while (i < data->obj_count && data->scene_objects[i].type != CAMERA_OBJ)
		i++;
	if (i == data->obj_count)
		return ;
	data->view_rays = set_view_rays(&data->view_rays, data->main_window,
			data->scene_objects[i], needs_alloc);
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
	get_main_view_rays(&data, true);
	redraw_main_window(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
