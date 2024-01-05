/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:13:45 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/04 23:45:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to handle the keys pressed in association with the L_CTRL key.
 * If one of the following shortcuts is triggered, redraws the render window.
 * <CTRL-u>	: increase the virtual pixels = decrease the resolution.
 * <CTRL-d> : decrease the virtual pixels = increase the resolution.
 * <CTRL-a> : switch ON/OFF the anti-aliasing.
 *
 * @param int keycode	-> X11 keycode of the pressed key to check
 * @param t_data *data	-> the program's data to modify at matching shortcut
 */
static void	control_key_handler(int keycode, t_data *data)
{
	if (keycode == XK_u)
	{
		set_window_pixel_ratio(&data->render_window,
			data->render_window.pixel_ratio + 5);
		data->render_window.draw_pos[0] = 0;
		data->render_window.draw_pos[1] = 0;
		get_main_view_rays(data, true);
	}
	if (keycode == XK_d)
	{
		set_window_pixel_ratio(&data->render_window,
			data->render_window.pixel_ratio - 5);
		data->render_window.draw_pos[0] = 0;
		data->render_window.draw_pos[1] = 0;
		get_main_view_rays(data, true);
	}
	if (keycode == XK_a)
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
 * A camera movement triggers the recalculation of the view rays and redraws the
 * render window.
 *
 * @param int keycode	-> X11 keycode of the pressed key to check
 * @param t_data *data	-> pointer to the data to modify at matching keypress
 */
static void	camera_move_check(int keycode, t_data *data)
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
		return ;
	set_object_coords(data->active_camera, coos);
	set_view_rays(&data->view_rays, data->render_window,
		*(data->active_camera), false);
	data->render_window.draw_pos[0] = 0;
	data->render_window.draw_pos[1] = 0;
}

/*
 * Function to interpret a keyboard key press.
 * Saves the L_CTRL key press in the program data to enable shortcuts with it.
 *
 * @param int keycode		-> X11 keycode of the pressed key
 * @param t_data *data		-> pointer to the data to modify with the key press
 * @[redundant]return int	-> 0
 */
int	key_press_handler(int keycode, t_data *data)
{
	if (keycode == XK_Control_L)
		data->control_key = true;
	if (keycode == XK_Escape)
		free_and_exit(data);
	if (data->control_key)
		control_key_handler(keycode, data);
	camera_move_check(keycode, data);
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
