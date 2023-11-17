/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:47:33 by leudelin          #+#    #+#             */
/*   Updated: 2023/11/17 14:47:35 by leudelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_range_numbers_part3(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (!ft_strncmp(block[i][0], "pl", 2))
			{
				check_range_vectors(block[i][2]);
				check_range_color(block[i][3]);
			}
			if (!strncmp(block[i][0], "cy", 3))
			{
				check_range_vectors(block[i][2]);
				check_range_color(block[i][5]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_range_numbers_part2(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (!ft_strncmp(block[i][0], "L", 2))
			{
				check_range_light(block[i][2]);
				check_range_color(block[i][3]);
			}
			if (!strncmp(block[i][0], "sp", 3))
			{
				check_range_color(block[i][3]);
			}
			j++;
		}
		i++;
	}
	check_range_numbers_part3(block);
	return (0);
}

int	check_range_numbers(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (!strncmp(block[i][0], "A", 2))
			{
				check_range_light(block[i][1]);
				check_range_color(block[i][2]);
			}
			if (!ft_strncmp(block[i][0], "C", 2))
			{
				check_range_vectors(block[i][2]);
				check_range_fov(block[i][3]);
			}
			j++;
		}
		i++;
	}
	check_range_numbers_part2(block);
	return (0);
}
