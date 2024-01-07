/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 14:31:30 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to free the program data and exit with code 0.
 *
 * @param t_data *data	-> pointer to the data to free
 * @noreturn int		-> needed for the minilibx hooking to the function
 */
noreturn int	free_and_exit(t_data *data)
{
	free_data(data);
	exit(0);
}

/*
 * Function to free the program data.
 * 
 * @param t_data *data	-> pointer to the data to free
 */
void	free_data(t_data *data)
{
	int	i;

	if (data->scene_objects)
		free(data->scene_objects);
	if (data->mlx_ptr)
	{
		my_destroy_window(data->mlx_ptr, &data->render_window);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (!data->view_rays)
		return ;
	i = 0;
	while (data->view_rays[i])
		free(data->view_rays[i++]);
	free(data->view_rays);
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
static int	initialize_mlx(t_data *data)
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

/*
 * Function to initialize the parameter data by reading the parameter scene file.
 * Display an error message and exit with a status code if the file is invalid
 * or a fatal error occured.
 *
 * @param t_data *data			-> pointer to the data to initialize
 * @param const char *file_name	-> name of the file to read for initialization
 * @return int					-> status code of the function
 */
static int	init_data(t_data *data, const char *file_name)
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
		return (free_double_pointer((void **) file_split), status);
	status = initialize_object(data, file_split);
	if (status != 0 && status != RTSUCCESS)
		return (free_double_pointer((void **) file_split), status);
	free_double_pointer((void **) file_split);
	data->anti_aliasing = true;
	return (initialize_mlx(data));
}

/*
 * Main function of the program.
 * Initializes the program data and the minilibx instance by reading the arguemnt
 * scene file. On success, starts the drawing of the render window and loops
 * waiting for user input until the user quits or a fatal error occurs.
 * Displays an error message and exits with an error code if the argument scene
 * file is invalid or a fatal error occured.
 *
 * @params int argc		-> number of arguments
 * @params char **argv	-> 1 additional argument expected : the scene file
 * @return int			-> status code of the program
 */
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
	mlx_loop(data.mlx_ptr);
	return (0);
}
