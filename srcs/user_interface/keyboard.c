/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 17:11:48 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_coords	axial_coords_move(t_coords origin, t_vector axis, int distance)
{
	return ((t_coords){origin.x + axis.x * distance,
		origin.y + axis.y * distance, origin.z + axis.z * distance});
}

static void	move_object(int keycode, t_object *to_move, t_basis basis,
	bool amplify)
{
	size_t		amplifier;
	t_coords	coords;

	amplifier = 1 + amplify * 3;
	if (keycode == XK_Up)
		coords = axial_coords_move(to_move->coords, basis.x, 10 * amplifier);
	if (keycode == XK_Down)
		coords = axial_coords_move(to_move->coords, basis.x, -10 * amplifier);
	if (keycode == XK_Right)
		coords = axial_coords_move(to_move->coords, basis.y, -10 * amplifier);
	if (keycode == XK_Left)
		coords = axial_coords_move(to_move->coords, basis.y, 10 * amplifier);
	if (keycode == XK_space)
		coords = axial_coords_move(to_move->coords, basis.z, 10 * amplifier);
	if (keycode == XK_Shift_L)
		coords = axial_coords_move(to_move->coords, basis.z, -10 * amplifier);
	set_object_coords(to_move, coords);
}

int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == XK_Control_L)
		data->control_key = false;
	return (0);
}

/*
 * Function to interpret a keyboard key press.
 *
 * @param int keycode	-> key code/index of the pressed key
 * @param t_data *data	-> pointer to the data to modify with the key press
 * @return int			-> status code of the function
 */
int	key_press_handler(int keycode, t_data *data)
{
	t_object	*camera;

	if (keycode == XK_Control_L)
		data->control_key = true;
	if (keycode == XK_Escape)
		free_and_exit(data);
	if (data->control_key)
	{
		if (keycode == XK_u)
		{
			set_window_pixel_ratio(&data->main_window,
				data->main_window.pixel_ratio + 5);
			data->main_window.draw_pos[0] = 0;
			data->main_window.draw_pos[1] = 0;
			get_main_view_rays(data, true);
		}
		if (keycode == XK_d)
		{
			set_window_pixel_ratio(&data->main_window,
				data->main_window.pixel_ratio - 5);
			data->main_window.draw_pos[0] = 0;
			data->main_window.draw_pos[1] = 0;
			get_main_view_rays(data, true);
		}
	}
	if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Right
		|| keycode == XK_Left || keycode == XK_space || keycode == XK_Shift_L)
	{
		camera = get_object_ptr(CAMERA_OBJ, data->scene_objects,
				data->obj_count);
		if (!camera)
			return (1);
		move_object(keycode, camera, camera->local_basis, data->control_key);
		set_view_rays(&data->view_rays, data->main_window, *camera, false);
		data->main_window.draw_pos[0] = 0;
		data->main_window.draw_pos[1] = 0;
	}
	if (keycode == XK_F1)
	{
		data->anti_aliasing = !data->anti_aliasing;
		data->main_window.draw_pos[0] = 0;
		data->main_window.draw_pos[1] = 0;
	}
	redraw_main_window(data);
	return (0);
}

/*
 * Function to set up the keyboard key hooks for the minilibx.
 * The 'KeyPressMask' applies to when a key starts being pressed.
 * The 'KeyReleaseMask' applies to when a key stops being pressed.
 * The 'DestroyNotify' event triggers at a click on the window closing cross.
 *
 * @param t_data *data	-> pointer to the data to act on with the key presses
 */
void	init_key_hooks(t_data *data)
{
	mlx_hook(data->main_window.ptr, KeyPress, KeyPressMask,
		&key_press_handler, data);
	mlx_hook(data->main_window.ptr, KeyRelease, KeyReleaseMask,
		&key_release_handler, data);
	mlx_hook(data->main_window.ptr, DestroyNotify, NoEventMask, &free_and_exit,
		data);
	mlx_loop_hook(data->mlx_ptr, &redraw_main_window, data);
}
