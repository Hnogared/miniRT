/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 11:14:56 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		free_and_exit(data);
	redraw_main_window(data);
	return (0);
}

void	init_key_hooks(t_data *data)
{
//	mlx_loop_hook(data->ptr, &disp_main_image, data);
	mlx_hook(data->main_window.ptr, KeyPress, KeyPressMask, &key_handler, data);
	mlx_hook(data->main_window.ptr, DestroyNotify, NoEventMask, &free_and_exit,
		data);
}
