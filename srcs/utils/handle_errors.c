/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:38:24 by motoko            #+#    #+#             */
/*   Updated: 2023/11/29 17:43:16 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_perror(char *prefix, char *error_tab[RTERR_COUNT], int errnum)
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
}

void	ft_panic(t_data *data, char *prefix, int errnum)
{
	exit(ft_perror(prefix, data->error_tab, errnum));
}

/*
void	free_parsing_and_exit(t_data *data, char ***block)
{
	int	i;

	i = 0;
	if (!block)
		return ;
	while (block[i])
	{
		free_str_tab(block[i]);
		i++;
	}
	free(block);
	exit(0);
}
*/

void	err(char *str)
{
	printf("%s\n", str);
	exit(0);
}
