/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:59 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/27 15:14:33 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_atof(const char *nptr)
{
	int		i;
	int		sign;
	float	nbr;
	int		divider;

	i = 0;
	nbr = 0.0;
	sign = 1;
	divider = 10;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr *= 10;
		nbr += (float)(nptr[i] - '0');
		i++;
	}
	i++;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr += (float)(nptr[i] - '0') / divider;
		divider *= 10;
		i++;
	}
	return (nbr * sign);
}
