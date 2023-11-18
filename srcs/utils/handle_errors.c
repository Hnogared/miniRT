/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:38:24 by motoko            #+#    #+#             */
/*   Updated: 2023/11/18 17:23:53 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_perror(char *prefix, char *err_str, int errnum)
{
	ft_fprintf(STDERR_FILENO, PROG_NAME);
	if (prefix)
		ft_fprintf(STDERR_FILENO, ": %s", prefix);
	if (errnum < MAX_STD_ERROR)
	{
		ft_fprintf(STDERR_FILENO, ": ");
		perror(NULL);
		return (errnum);
	}
	if (err_str)
		ft_fprintf(STDERR_FILENO, ": %s", err_str);
	ft_fprintf(STDERR_FILENO, "\n");
	return (errnum - 1 - MAX_STD_ERROR);
}

void	init_error_tab(char *error_tab[RTERR_COUNT])
{
	error_tab[0] = "test";
}

void	err(char *str)
{
	printf("%s\n", str);
	exit(0);
}
