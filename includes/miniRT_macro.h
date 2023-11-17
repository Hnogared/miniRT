/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_macro.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:25 by motoko            #+#    #+#             */
/*   Updated: 2023/11/17 14:34:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MACRO_H
# define MINIRT_MACRO_H

/*
 * Program main window width override.
 * If equal to 0, the main window takes the width of the computer screen.
 * Use WIN_WIDTH=<value> with make / the compilation flag -D WIN_WIDTH=<value>.
 */
# ifndef WIN_WIDTH
#  define WIN_WIDTH		0
# endif

/*
 * Program main window height override.
 * If equal to 0, the main window takes the height of the computer screen.
 * Use WIN_HEIGHT=<value> with make / the compilation flag -D WIN_HEIGHT=<value>.
 */
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	0
# endif

# define BUFFER_SIZE 1000

# define SYNTAX_ERROR 2

/* Different scene object types (see the t_object structure @ miniRT_struct.h) */
# define BLANK_OBJ		0
# define CAMERA_OBJ		1
# define LIGHT_OBJ		2
# define SPHERE_OBJ		3
# define PLANE_OBJ		4
# define CYLINDER_OBJ	5

# define FILE_NAME "error: must end with .rt" 
# define OPEN_FILE "error: open file"
# define READ_FILE "error: read file"
# define INVALID_OBJECT "error: invalid object"
# define IS_NOT_VALID "error: not a valid argument"
# define IS_NOT_NUMBER "error: not a number"
# define DUPLICATE_OBJ "error: duplicate object"
# define TOO_MANY_COMMA "error: to many comma in number"
# define TOO_MANY_DOT "error: to many dot in number"
#endif
