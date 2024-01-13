/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:59 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 21:36:26 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function to convert an untrimmed string into an int.
 * Whitespaces at the beginning of the string are skipped. The conversion ends
 * at the last digit of the number, following characters ar ignored.
 *
 * @param const char *nptr	-> pointer to the strong to convert
 * @return int				-> the resulting converted integer
 */
int	ft_atoi(const char *nptr)
{
	int		i;
	int		nbr;
	int		sign;

	i = 0;
	nbr = 0;
	while (ft_iswhitespace(nptr[i]))
		i++;
	sign = 1 - 2 * (nptr[i] == '-');
	i += (nptr[i] == '-' || nptr[i] == '+');
	while (ft_isdigit(nptr[i]))
	{
		nbr *= 10;
		nbr += nptr[i++] - '0';
	}
	return (nbr * sign);
}
