/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:38:24 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 14:09:58 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to either display an errno error message or a custom error message
 * from the parameter error messages array depending on the parameter errnum.
 * The error message is preceeded by the defined PROG_NAME and the parameter
 * prefix if not NULL.
 * errnum < FIRST_ERRVAL  : errno error message
 * errnum >= FIRST_ERRVAL : custom error message from error_tab[RTERR_COUNT]
 *
 * @param const char *prefix	-> string to display before the error if not NULL
 * @param char *const error_tab[RTERR_COUNT]	-> error messages array to read
 * @param unsigned int errnum	-> the error number
 * @return unsigned int			-> the used converted error number
 */
unsigned int	ft_perror(const char *prefix,
	char *const error_tab[RTERR_COUNT], unsigned int errnum)
{
	ft_fprintf(STDERR_FILENO, PROG_NAME);
	if (errnum < FIRST_ERRVAL)
	{
		ft_fprintf(STDERR_FILENO, ": ");
		perror(prefix);
		return (errnum);
	}
	if (prefix)
		ft_fprintf(STDERR_FILENO, ": %s", prefix);
	ft_fprintf(STDERR_FILENO, ": %s\n", error_tab[errnum - 1 - FIRST_ERRVAL]);
	return (errnum - 1 - FIRST_ERRVAL);
}

/*
 * Function to initialize all the error messages inside the parameter array.
 *
 * @param char *error_tab[RTERR_COUNT]	-> strings array to initialize
 */
void	init_error_tab(char *error_tab[RTERR_COUNT])
{
	error_tab[0] = RTSUCCESS_MSG;
	error_tab[1] = RTERR_MSG;
	error_tab[2] = RTERR_ARGS_COUNT_MSG;
	error_tab[3] = RTERR_INVALID_ARG_MSG;
	error_tab[4] = RTERR_FILE_NAME_MSG;
	error_tab[5] = RTERR_OPEN_FILE_MSG;
	error_tab[6] = RTERR_READ_FILE_MSG;
	error_tab[7] = RTERR_OBJ_MSG;
	error_tab[8] = RTERR_DUPLIC_OBJ_MSG;
	error_tab[9] = RTERR_OBJS_COUNT_MSG;
	error_tab[10] = RTERR_COLOR_MSG;
	error_tab[11] = RTERR_FOV_MSG;
	error_tab[12] = RTERR_VECTOR_MSG;
	error_tab[13] = RTERR_BRIGHTNESS_MSG;
	error_tab[14] = RTERR_NUM_MSG;
	error_tab[15] = RTERR_NUM_COMMA_MSG;
	error_tab[16] = RTERR_NUM_DOT_MSG;
	error_tab[17] = RTERR_OPEN_WIN_MSG;
}
