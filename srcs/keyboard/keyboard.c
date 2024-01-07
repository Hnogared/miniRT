/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 22:12:31 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to handle the keys pressed in association with the L_CTRL key.
 * If one of the following shortcuts is triggered, redraws the render window.
 * <CTRL-r>	: increase the virtual pixels = decrease the resolution.
 * <CTRL-f> : decrease the virtual pixels = increase the resolution.
 * <CTRL-t> : switch ON/OFF the anti-aliasing.
 *
 * @param int keycode	-> X11 keycode of the pressed key to check
 * @param t_data *data	-> the program's data to modify at matching shortcut
 *
 * @parent_func key_press_handler	-> function to interpret a keyboard press
 */
static void	control_key_handler(int keycode, t_data *data)
{
	if (keycode == XK_r)
	{
		set_window_pixel_ratio(&data->render_window,
			data->render_window.pixel_ratio + 5);
		data->render_window.draw_pos[0] = 0;
		data->render_window.draw_pos[1] = 0;
		get_render_view_rays(data, true);
	}
	if (keycode == XK_f)
	{
		set_window_pixel_ratio(&data->render_window,
			data->render_window.pixel_ratio - 5);
		data->render_window.draw_pos[0] = 0;
		data->render_window.draw_pos[1] = 0;
		get_render_view_rays(data, true);
	}
	if (keycode == XK_t)
	{
		data->anti_aliasing = !data->anti_aliasing;
		data->render_window.draw_pos[0] = 0;
		data->render_window.draw_pos[1] = 0;
	}
}

/*
 * Function to move the scene's active camera at a movement key press.
 * <U_arrow> : move the camera forward relative to its local basis (x axis ++). 
 * <D_arrow> : move the camera backward relative to its local basis (x axis --).
 * <R_arrow> : move the camera right relative to its local basis (y axis --).
 * <L_arrow> : move the camera left relative to its local basis (y axis ++).
 * <spacebar>: move the camera up relative to its local basis (z axis ++).
 * <L_shift> : move the camera down relative to its local basis (z axis --).
 * If a movement key is pressed in association with the L_CTRL key, the movement
 * distance is increased.
 *
 * @param int keycode	-> X11 keycode of the pressed key to check
 * @param t_data *data	-> pointer to the data to modify at matching keypress
 * @return int			-> 1 if the camera was moved, 0 otherwise
 *
 * @parent_func key_press_handler	-> function to interpret a keyboard press
 */
static int	camera_move_check(int keycode, t_data *data)
{
	int			distance;
	t_basis		basis;
	t_coords	coos;

	basis = data->active_camera->local_basis;
	distance = (3 * data->control_key + 1) * 10;
	if (keycode == XK_Up)
		coos = advance_on_vec(data->active_camera->coords, basis.x, distance);
	else if (keycode == XK_Down)
		coos = advance_on_vec(data->active_camera->coords, basis.x, -distance);
	else if (keycode == XK_Right)
		coos = advance_on_vec(data->active_camera->coords, basis.y, -distance);
	else if (keycode == XK_Left)
		coos = advance_on_vec(data->active_camera->coords, basis.y, distance);
	else if (keycode == XK_space)
		coos = advance_on_vec(data->active_camera->coords, basis.z, distance);
	else if (keycode == XK_Shift_L)
		coos = advance_on_vec(data->active_camera->coords, basis.z, -distance);
	else
		return (0);
	set_object_coords(data->active_camera, coos);
	return (1);
}

/*
 * Function to rotate the scene's active camera at a rotation key press.
 * <w> : pitch the camera up relative to its local basis (y axis ++).
 * <s> : pitch the camera down relative to its local basis (y axis --).
 * <d> : yaw the camera right relative to its local basis (z axis ++).
 * <a> : yaw the camera left relative to its local basis (z axis --).
 * <e> : roll the camera right relative to its local basis (x axis ++).
 * <q> : roll the camera left relative to its local basis (x axis --).
 * If a rotation key is pressed in association with the L_CTRL key, the rotation
 * angle is increased.
 *
 * @param int keycode	-> X11 keycode of the pressed key to check
 * @param t_data *data	-> pointer to the data to modify at matching keypress
 * @return int			-> 1 if the camera was rotated, 0 otherwise
 *
 * @parent_func key_press_handler	-> function to interpret a keyboard press
 */
static int	camera_rotate_check(int keycode, t_data *data)
{
	float	angle;
	t_basis	camera_basis;

	angle = (3 * data->control_key + 1) * 10;
	camera_basis = data->active_camera->local_basis;
	if (keycode == XK_w)
		rotate_object(data->active_camera, -angle, camera_basis.y);
	if (keycode == XK_s)
		rotate_object(data->active_camera, angle, camera_basis.y);
	if (keycode == XK_d)
		rotate_object(data->active_camera, -angle, camera_basis.z);
	if (keycode == XK_a)
		rotate_object(data->active_camera, angle, camera_basis.z);
	if (keycode == XK_e)
		rotate_object(data->active_camera, angle, camera_basis.x);
	if (keycode == XK_q)
		rotate_object(data->active_camera, -angle, camera_basis.x);
	return (keycode == XK_w || keycode == XK_s || keycode == XK_d
		|| keycode == XK_a || keycode == XK_e || keycode == XK_q);
}

/*
 * Function to interpret a keyboard key press.
 * Saves the L_CTRL key press in the program data to enable shortcuts with it.
 * A camera movement or rotation triggers the recalculation of the view rays
 * and redraws the render window.
 *
 * @param int keycode		-> X11 keycode of the pressed key
 * @param t_data *data		-> pointer to the data to modify with the key press
 * @[redundant]return int	-> 0
 *
 * @child_func camera_rotate_check	-> function to rotate the camera at key press
 * @child_func camera_move_check	-> function to move the camera at key press
 * @child_func control_key_handler	-> function to handle L_CTRL shortcuts
 */
int	key_press_handler(int keycode, t_data *data)
{
	if (keycode == XK_Control_L)
		data->control_key = true;
	if (keycode == XK_Escape)
		free_and_exit(data);
	if (data->control_key)
		control_key_handler(keycode, data);
	if (camera_move_check(keycode, data) || camera_rotate_check(keycode, data))
	{
		get_render_view_rays(data, false);
		data->render_window.draw_pos[0] = 0;
		data->render_window.draw_pos[1] = 0;
	}
	redraw_render_window(data);
	return (0);
}

/*
 * Function to interpret a keyboard pressed key release.
 * Saves the L_CTRL key release in the program data to enable shortcuts with it.
 *
 * @param int keycode		-> X11 keycode of the released key
 * @param t_data *data		-> pointer to the data to modify with the key press
 * @[redundant]return int	-> 0
 */
int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == XK_Control_L)
		data->control_key = false;
	return (0);
}
