/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:46:03 by leudelin          #+#    #+#             */
/*   Updated: 2023/12/03 10:40:29 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_range_fov(char *fov)
{
	int	temp;
	int		status;

	status = 0;
	temp = ft_atoi(fov);
	if (!status && (temp < 0 || temp > 180))
		status = RTERR_FOV;
	return (status);
}

int	check_range_vectors(char *str)
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
		if (!status && (temp < -1 || temp > 1))
			status = RTERR_VECTOR;
		i++;
	}
	free_str_tab(split);
	return (status);
}

int	check_range_color(char *str)
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
	free_str_tab(split);
	return (status);
}

int	check_range_light(char *str)
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
		if (!status && (temp < 0 || temp > 1))
			status = RTERR_BRIGHTNESS;
		i++;
	}
	free_str_tab(split);
	return (status);
}
