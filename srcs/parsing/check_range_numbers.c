/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:47:33 by leudelin          #+#    #+#             */
/*   Updated: 2024/01/07 15:14:54 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_range_numbers_part1(const char ***block, int i)
{
	int	status;

	status = 0;
	if (!strncmp(block[i][0], "A", 2))
	{
		status = check_range_light(block[i][1]);
		if (status)
			return (status);
		status = check_range_color(block[i][2]);
		if (status)
			return (status);
	}
	if (!ft_strncmp(block[i][0], "C", 2))
	{
		status = check_range_vectors(block[i][2]);
		if (status)
			return (status);
		status = check_range_fov(block[i][3]);
		if (status)
			return (status);
	}
	return (status);
}

static int	check_range_numbers_part2(const char ***block, int i)
{
	int	status;

	status = 0;
	if (!ft_strncmp(block[i][0], "L", 2))
	{
		status = check_range_light(block[i][2]);
		if (status)
			return (status);
		status = check_range_color(block[i][3]);
		if (status)
			return (status);
	}
	if (!strncmp(block[i][0], "sp", 3))
	{
		status = check_range_color(block[i][3]);
		if (status)
			return (status);
	}
	return (status);
}

static int	check_range_numbers_part3(const char ***block, int i)
{
	int	status;

	status = 0;
	if (!ft_strncmp(block[i][0], "pl", 2))
	{
		status = check_range_vectors(block[i][2]);
		if (status)
			return (status);
		status = check_range_color(block[i][3]);
		if (status)
			return (status);
	}
	if (!strncmp(block[i][0], "cy", 3))
	{
		status = check_range_vectors(block[i][2]);
		if (status)
			return (status);
		status = check_range_color(block[i][5]);
		if (status)
			return (status);
	}
	return (status);
}

int	check_range_numbers(const char ***block)
{
	int	i;
	int	j;
	int	status;

	status = 0;
	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			status = check_range_numbers_part1(block, i);
			if (status)
				return (status);
			status = check_range_numbers_part2(block, i);
			if (status)
				return (status);
			status = check_range_numbers_part3(block, i);
			if (status)
				return (status);
			j++;
		}
		i++;
	}
	return (0);
}
