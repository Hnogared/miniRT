/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:59 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/11 22:08:52 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_neg(const char *nptr)
{
	return (-1 * (nptr[0] == '-') + (nptr[0] != '-'));
}

static float	create_nbr(const char *nptr)
{
	int		divider;
	int		i;
	float	nbr;

	i = 0;
	nbr = 0.0;
	divider = 10;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr *= 10;
		nbr += (float)(nptr[i] - '0');
		i++;
	}
	if (!nptr[i])
		return (nbr);
	while (nptr[++i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr += (float)(nptr[i] - '0') / divider;
		divider *= 10;
	}
	return (nbr);
}

float	ft_atof(const char *nptr)
{
	char	*temp_nptr;

	if (!nptr)
		return (0.0f);
	temp_nptr = (char *) nptr;
	while (*temp_nptr
		&& ((*temp_nptr >= 9 && *temp_nptr <= 13) || *temp_nptr == 32))
		temp_nptr++;
	if (!*temp_nptr)
		return (0.0f);
	return (create_nbr(temp_nptr) * (float) is_neg(temp_nptr));
}
