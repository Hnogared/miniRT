/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:34:05 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/06 10:34:32 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close_cross(int keycode, t_data *data)
{
	(void)keycode;
    mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	(void)argc;
	(void)argv;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello Wolrd !");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	i = 0;
	while (i < 1000)
	{
		my_mlx_pixel_put(&data, i, i, 0x00FF0000); //rouge
		my_mlx_pixel_put(&data, 5, i, 0x000000FF); //bleu
		my_mlx_pixel_put(&data, i, 5, 0x0000FF00); //vert
		i++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_key_hook(data.mlx_win, close_cross, &data); // evenement clavier
	mlx_hook(data.mlx_win, 4, 1L<<0, close, &data); // evenement souris
	mlx_loop(data.mlx);
	return (0);
}
