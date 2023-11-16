/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_macro.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:18:25 by motoko            #+#    #+#             */
/*   Updated: 2023/11/13 21:21:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MACRO_H
# define MINIRT_MACRO_H

# ifndef WIN_WIDTH
#  define WIN_WIDTH		0
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	0
# endif

# define BUFFER_SIZE 1000

# define FILE_NAME "error: must end with .rt" 
# define OPEN_FILE "error: open file"
# define READ_FILE "error: read file"
# define INVALID_OBJECT "error: invalid object"
# define IS_NOT_VALID "error: not a valid argument"
# define IS_NOT_NUMBER "error: not a number"
# define DUPLICATE_OBJ "error: duplicate object"
# define TOO_MANY_COMMA "error: too many comma in number"
# define TOO_MANY_DOT "error: too many dot in number"
# define TOO_MANY_OBJS "error : too many objects"
# define COLOR_NOT_GOOD "error : wrong arguments for colors"
# define WRONG_FOV "error : FOV must be between 0 and 180"
# define RANGE_VECTOR "error : vectors can only be between -1 and 1"
# define RANGE_LIGHT "error : light can only be between 0 and 1"

#endif