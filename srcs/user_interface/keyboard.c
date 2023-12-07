/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/07 16:16:22 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_coords	axial_coords_move(t_coords origin, t_vector axis, int distance)
{
	return ((t_coords){origin.x + axis.x * distance,
		origin.y + axis.y * distance, origin.z + axis.z * distance});
}

static void	move_object(int keycode, t_object *to_move, t_basis basis)
{
	t_coords	coords;

	if (keycode == XK_Up)
		coords = axial_coords_move(to_move->coords, basis.x, 10);
	if (keycode == XK_Down)
		coords = axial_coords_move(to_move->coords, basis.x, -10);
	if (keycode == XK_Right)
		coords = axial_coords_move(to_move->coords, basis.y, -10);
	if (keycode == XK_Left)
		coords = axial_coords_move(to_move->coords, basis.y, 10);
	set_object_coords(to_move, coords);
}

/*
 * Function to interpret a keyboard key press.
 *
 * @param int keycode	-> key code/index of the pressed key
 * @param t_data *data	-> pointer to the data to modify with the key press
 * @return int			-> status code of the function
 */
int	key_handler(int keycode, t_data *data)
{
	t_object	*camera;

	if (keycode == XK_Escape)
		free_and_exit(data);
	if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Right
		|| keycode == XK_Left)
	{
		camera = get_object_ptr(CAMERA_OBJ, data->scene_objects,
				data->obj_count);
		if (!camera)
			return (1);
		move_object(keycode, camera, camera->local_basis);
		set_view_rays(&data->view_rays, data->main_window, *camera, false);
	}
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
//	mlx_loop_hook(data->ptr, &disp_main_image, data);
void	init_key_hooks(t_data *data)
{
	mlx_hook(data->main_window.ptr, KeyPress, KeyPressMask, &key_handler, data);
	mlx_hook(data->main_window.ptr, DestroyNotify, NoEventMask, &free_and_exit,
		data);
}
