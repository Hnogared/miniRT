/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:46:03 by leudelin          #+#    #+#             */
/*   Updated: 2024/01/07 17:34:18 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to check if the parameter
 */
int	check_range_fov(const char *fov)
{
	int	temp;
	int	status;

	status = 0;
	temp = ft_atoi(fov);
	if (!status && (temp < 0 || temp > 180))
		status = RTERR_FOV;
	return (status);
}

int	check_range_vectors(const char *str)
{
	char	**split;
	int		i;
	int		status;
	float	temp;

	status = 0;
	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	{
		temp = ft_atof(split[i]);
		if (!status && (temp < -1.0f || temp > 1.0f))
			status = RTERR_VECTOR;
		i++;
	}
	free_double_pointer((void **) split);
	return (status);
}

int	check_range_color(const char *str)
{
	char	**split;
	int		temp;
	int		i;
	int		status;

	status = 0;
	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	{
		temp = ft_atoi(split[i]);
		if (!status && (temp > 255 || temp < 0))
			status = RTERR_COLOR;
		i++;
	}
	free_double_pointer((void **) split);
	return (status);
}

int	check_range_light(const char *str)
{
	char	**split;
	int		i;
	int		status;
	float	temp;

	status = 0;
	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	{
		temp = ft_atof(split[i]);
		if (!status && (temp < 0.0f || temp > 1.0f))
			status = RTERR_BRIGHTNESS;
		i++;
	}
	free_double_pointer((void **) split);
	return (status);
}
