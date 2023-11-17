/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_number1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:46:03 by leudelin          #+#    #+#             */
/*   Updated: 2023/11/17 14:46:05 by leudelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_range_fov(char *fov)
{
	int	temp;

	temp = ft_atoi(fov);
	if (temp < 0 || temp > 180)
		err(WRONG_FOV);
	return (0);
}

int	check_range_vectors(char *str)
{
	char	**split;
	int		temp;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	{
		temp = ft_atoi(split[i]);
		if (temp < -1 || temp > 1)
			err(RANGE_VECTOR);
		i++;
	}
	return (0);
}

int	check_range_color(char *str)
{
	char	**split;
	int		temp;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	{
		temp = ft_atoi(split[i]);
		if (temp > 255 || temp < 0)
			err(COLOR_NOT_GOOD);
		i++;
	}
	return (0);
}

int	check_range_light(char *str)
{
	char	**split;
	int		temp;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	{
		temp = ft_atoi(split[i]);
		if (temp < 0 || temp > 1)
			err(RANGE_LIGHT);
		i++;
	}
	return (0);
}
