/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:59 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/19 00:07:53 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

/*
 * Function to convert a trimmed string into a float.
 *
 * @param const char *nptr	-> pointer to the string to convert
 * @return float			-> the resulting float conversion
 *
 * @parent_func	ft_atof	-> function to convert an untrimmed string into a float
 */
static float	create_nbr(const char *nptr)
{
	int		divider;
	int		i;
	int		sign;
	float	nbr;

	nbr = 0;
	sign = 1 - 2 * (nptr[0] == '-');
	i = (nptr[0] == '-' || nptr[0] == '+');
	while (nptr[i] && ft_iswhitespace(nptr[i]))
		i++;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nbr *= 10;
		nbr += (float)(nptr[i++] - '0');
	}
	if (!nptr[i] || (nptr[i] != '.' && nptr[i] != ','))
		return (nbr * sign);
	divider = 10;
	i++;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nbr += (float)(nptr[i++] - '0') / divider;
		divider *= 10;
	}
	return (nbr * (float) sign);
}

/*
 * Function to convert a string into a float.
 * Whitespaces present at the beginning of the string are skipped. The conversion
 * ends at the last number character, the following ones are ignored.
 *
 * @param const char *nptr	-> pointer to the string to convert
 * @return float			-> the resulting float conversion
 *
 * @child_func create_nbr	-> function to convert a trimmd string into a float
 */
float	ft_atof(const char *nptr)
{
	char	*temp_nptr;

	if (!nptr)
		return (0.0f);
	temp_nptr = (char *) nptr;
	while (*temp_nptr && ft_iswhitespace(*temp_nptr))
		temp_nptr++;
	if (!*temp_nptr)
		return (0.0f);
	return (create_nbr(temp_nptr));
}
