/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/04 23:46:07 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_main_view_rays(t_data *data, bool needs_alloc)
{
	int	status;

	status = set_view_rays(&data->view_rays, data->render_window,
			*(data->active_camera), needs_alloc);
	if (status != 0)
	{
		status = ft_perror(NULL, data->error_tab, status);
		free_data(data);
		exit(status);
	}
}

/*
 * Function to intialise the program's minilibx instance.
 * Opens the program's render window displaying the raytracing results.
 * Sets up the events hooks (e.g a key press) for the minilibx.
 * The 'KeyPressMask' applies to when a key starts being pressed.
 * The 'KeyReleaseMask' applies to when a key stops being pressed.
 * The 'DestroyNotify' event triggers at a click on the window closing cross.
 *
 * @param t_data *data	-> pointer to the data to initialize the mlx instance
 */
int	initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (open_render_window(data, "miniRT"))
		return (RTERR_OPEN_WIN);
	mlx_hook(data->render_window.ptr, KeyPress, KeyPressMask,
		&key_press_handler, data);
	mlx_hook(data->render_window.ptr, KeyRelease, KeyReleaseMask,
		&key_release_handler, data);
	mlx_hook(data->render_window.ptr, DestroyNotify, NoEventMask,
		&free_and_exit, data);
	mlx_loop_hook(data->mlx_ptr, &redraw_render_window, data);
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
	redraw_render_window(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
