/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:16:01 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 14:16:33 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

/* ************************************************************************** */
/* keyboard.c                                                                 */
/* ************************************************************************** */
/*
 * Function to interpret a keyboard key press.
 * Saves the L_CTRL key press in the program data to enable shortcuts with it.
 * A camera movement or rotation triggers the recalculation of the view rays
 * and redraws the render window.
 *
 * @param int keycode		-> X11 keycode of the pressed key
 * @param t_data *data		-> pointer to the data to modify with the key press
 * @[redundant]return int	-> 0
 */
int	key_press_handler(int keycode, t_data *data);

/*
 * Function to interpret a keyboard pressed key release.
 * Saves the L_CTRL key release in the program data to enable shortcuts with it.
 *
 * @param int keycode		-> X11 keycode of the released key
 * @param t_data *data		-> pointer to the data to modify with the key press
 * @[redundant]return int	-> 0
 */
int	key_release_handler(int keycode, t_data *data);

#endif
