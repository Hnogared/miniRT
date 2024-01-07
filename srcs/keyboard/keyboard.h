/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:16:01 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 23:16:35 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

/* keyboard.c */
int	key_press_handler(int keycode, t_data *data);
int	key_release_handler(int keycode, t_data *data);

#endif
