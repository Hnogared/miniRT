/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/21 17:21:42 by hnogared         ###   ########.fr       */
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
		return (RTERR_OPEN_WIN);
	init_key_hooks(data);
	return (0);
}

int	init_data(t_data *data, const char *file_name)
{
	int		status;
	char	*file;
	char	**file_split;

	file = get_file(data, file_name);
	file_split = ft_split(file, '\n');
	free(file);
	if (!file_split)
		return (errno);
	status = check_scene(data, file_split);
	if (status != 0 && status != RTSUCCESS)
		return (free_str_tab(file_split), status);
	status = initialize_object(data, file_split);
	if (status != 0 && status != RTSUCCESS)
		return (free_str_tab(file_split), status);
	free_str_tab(file_split);
	data->anti_aliasing = true;
	return (initialize_mlx(data));
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			status;

	status = 0;
	ft_bzero(&data, sizeof(t_data));
	init_error_tab(data.error_tab);
	if (argc != 2)
		return (ft_perror(NULL, data.error_tab, RTERR_ARGS_COUNT));
	if (check_file(argv[1]) == -1)
		return (ft_perror(NULL, data.error_tab, RTERR_FILE_NAME));
	status = init_data(&data, argv[1]);
	if (status)
	{
		free_data(&data);
		return (status);
	}
	get_main_view_rays(&data, true);
	redraw_main_window(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
