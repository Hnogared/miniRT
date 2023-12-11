/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:59 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/11 08:18:20 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_neg(const char *nptr)
{
	int	i;

	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	return (1);
}

static int	create_nbr(const char *nptr)
{
	int		divider;
	int		i;
	float	nbr;

	i = 0;
	nbr = 0.0;
	divider = 10;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr *= 10;
		nbr += (float)(nptr[i] - '0');
		i++;
	}
	if (!nptr[i])
		return (nbr * is_neg(nptr));
	while (nptr[++i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr += (float)(nptr[i] - '0') / divider;
		divider *= 10;
	}
	return (nbr);
}

float	ft_atof(const char *nptr)
{
	int		i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	return (create_nbr(nptr) * is_neg(nptr));
}
