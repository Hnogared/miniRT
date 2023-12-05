/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/05 15:43:56 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to open the program's main window.
 * The window will have the computer screen's width if WIN_WIDTH <= 0.
 * The window will have the comupter screen's height - 100 if WIN_HEIGHT <= 0.
 *
 * @param t_data *data	-> pointer to the program data
 * @param char *title	-> title of the window seen on the window bar
 * @return int			-> status code of the function
 */
int	open_main_window(t_data *data, char *title)
{
	int	pixel_ratio;
	int	win_size[2];

	mlx_get_screen_size(data->mlx_ptr, &win_size[0], &win_size[1]);
	win_size[1] -= 100;
	if (WIN_WIDTH > 0 && WIN_WIDTH < win_size[0])
		win_size[0] = WIN_WIDTH;
	if (WIN_HEIGHT > 0 && WIN_HEIGHT < win_size[1])
		win_size[1] = WIN_HEIGHT;
	pixel_ratio = DEFAULT_PIXEL_RATIO + (DEFAULT_PIXEL_RATIO <= 0);
	data->main_window = my_new_window(data->mlx_ptr, win_size, pixel_ratio,
			title);
	return (data->main_window.ptr == NULL);
}

int	funky(t_data *data, int x, int y)
{
	int	color;

	color = *(int *)(unsigned char [4]){0, x * data->test,
		(y * data->test) | (x * data->test), 0};
	return (color);
}

int	ray_trace(t_data *data, int x, int y)
{
	//printf("Dans Ray trace !!!!!!!!!!!!!!\n");
	//print_vec(data->view_rays[x][y].vector);
	ray_advance(data, &data->view_rays[x][y]);
	if (data->view_rays[x][y].nb_ref)
	{
//		printf("touch(%d:%d)\n", x, y);
		return (0xFFFFFF);
	}
//	printf("loc(%d:%d)\n", x, y);
	return (0);
}

void	redraw_main_window(t_data *data)
{
	int	x;
	int	y;
	int	color;
	int	pixel_size[2];

	pixel_size[0] = data->main_window.pixel_ratio;
	pixel_size[1] = data->main_window.pixel_ratio;
	print_vector(data->view_rays[0][0].vector, NULL);
	print_vector(data->view_rays[data->main_window.width / pixel_size[0] - 1][data->main_window.height / pixel_size[1] - 1].vector, NULL);
	x = 0;
	y = 0;
	while (y < data->main_window.height / pixel_size[1])
	{
		color = ray_trace(data, x, y);
		my_put_square_to_window(&data->main_window,
			(int [2]){x * pixel_size[0], y * pixel_size[1]}, pixel_size, color);
		x++;
		if (x < data->main_window.width / pixel_size[0])
			continue ;
		x = 0;
		y++;
	}
	redraw_window(data->mlx_ptr, &data->main_window);
	mlx_string_put(data->mlx_ptr, data->main_window.ptr, 10, 20, 0xFFFFFF,
		"THIS IS A TEST TKT");
}
