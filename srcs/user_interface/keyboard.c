/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 13:41:31 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to react depending on the given keyboard key pressed.
 *
 * @param int keycode	-> key code/index of the pressed key
 * @param t_data *data	-> pointer to the data to act on with the key press
 * @return int			-> status code of the function
 */
int	key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		free_and_exit(data);
	if (keycode == XK_Up)
		data->test += 10;
	if (keycode == XK_Down)
		data->test -= 10;
	redraw_main_window(data);
	return (0);
}

/*
 * Function to set up the keyboard key hooks for the minilibx.
 * The 'KeyPressMask' applies to when a key begins to get pressed.
 * The 'DestroyNotify' event triggers at a click on the window closing cross.
 *
 * @param t_data *data	-> pointer to the data to act on with the key presses
 */
void	init_key_hooks(t_data *data)
{
//	mlx_loop_hook(data->ptr, &disp_main_image, data);
	mlx_hook(data->main_window.ptr, KeyPress, KeyPressMask, &key_handler, data);
	mlx_hook(data->main_window.ptr, DestroyNotify, NoEventMask, &free_and_exit,
		data);
}
