/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <hnogared@student.42perpigna      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:17:44 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/12 01:44:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdnoreturn.h>
# include <math.h>
# include <X11/Xlib.h>

/* ************************************************************************** */
/* libraries header files                                                     */
/* ************************************************************************** */
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/* ************************************************************************** */
/* macros and structures definitions header files                             */
/* ************************************************************************** */
# include "miniRT_macro.h"
# include "miniRT_struct.h"

/* ************************************************************************** */
/* modules function prototypes header files                                   */
/* ************************************************************************** */
# include "../srcs/basis/basis.h"
# include "../srcs/display/display.h"
# include "../srcs/object/object.h"
# include "../srcs/keyboard/keyboard.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/raytracing/raytracing.h"
# include "../srcs/vector/vector.h"

/* ************************************************************************** */
/* main.c                                                                     */
/* ************************************************************************** */
/*
 * Function to free the program data and exit with code 0.
 *
 * @param t_data *data	-> pointer to the data to free
 * @noreturn int		-> needed for the minilibx hooking to the function
 */
noreturn int	free_and_exit(t_data *data);

/*
 * Function to free the program data.
 * 
 * @param t_data *data	-> pointer to the data to free
 */
void			free_data(t_data *data);

#endif
