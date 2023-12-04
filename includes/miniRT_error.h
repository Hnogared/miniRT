/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:09:40 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/04 14:04:23 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_ERROR_H
# define MINIRT_ERROR_H

/* The program name to display in ft_perror */
# ifndef PROG_NAME
#  define PROG_NAME	"miniRT"
# endif

/* Value of the first custom error */
# define FIRST_ERRVAL	255

/* Total number of errors. Increment to add more errors */
# define RTERR_COUNT	18

/* ************************************************************************** */
/* Error codes to use for ft_perror */
# define RTSUCCESS				256
# define RTERR					257

# define RTERR_ARGS_COUNT		258
# define RTERR_INVALID_ARG		259

# define RTERR_FILE_NAME		260
# define RTERR_OPEN_FILE		261
# define RTERR_READ_FILE		262

# define RTERR_OBJ				263
# define RTERR_DUPLIC_OBJ		264
# define RTERR_OBJS_COUNT		265
# define RTERR_COLOR			266
# define RTERR_FOV				267
# define RTERR_VECTOR			268
# define RTERR_BRIGHTNESS		269

# define RTERR_NUM				270
# define RTERR_NUM_COMMA		271
# define RTERR_NUM_DOT			272

/* ************************************************************************** */
/* Error messages displayed by ft_perror */
# define RTSUCCESS_MSG			"success"
# define RTERR_MSG				"error"

# define RTERR_ARGS_COUNT_MSG	"invalid arguments count"
# define RTERR_INVALID_ARG_MSG	"not a valid argument"

# define RTERR_FILE_NAME_MSG	"invalid file name: exp <file_name>.rt"
# define RTERR_OPEN_FILE_MSG	"couldn't open file"
# define RTERR_READ_FILE_MSG	"couldn't read file"

# define RTERR_OBJ_MSG			"invalid object"
# define RTERR_DUPLIC_OBJ_MSG	"invalid object: duplicate object"
# define RTERR_OBJS_COUNT_MSG	"too many objects"
# define RTERR_COLOR_MSG		"invalid object: invalid color: exp 0:255"
# define RTERR_FOV_MSG			"invalid object: invalid FOV: exp 0:180"
# define RTERR_VECTOR_MSG		"invalid object: invalid vector: exp -1.:1."
# define RTERR_BRIGHTNESS_MSG	"invalid object: invalid brightness: exp 0.:1."

# define RTERR_NUM_MSG			"invalid number"
# define RTERR_NUM_COMMA_MSG	"invalid number: too many commas"
# define RTERR_NUM_DOT_MSG		"invalid number: too many dots"

/* ************************************************************************** */
int		ft_perror(char *prefix, char *error_tab[RTERR_COUNT], int errnum);
void	init_error_tab(char *error_tab[RTERR_COUNT]);

#endif
