/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:37:49 by motoko            #+#    #+#             */
/*   Updated: 2023/11/13 19:46:58 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_range_fov(char *fov)
{
	if (ft_atoi(fov) < 0 || ft_atoi(fov) > 180)
		err(WRONG_FOV);
}

void	check_range_vectors(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while(split[i])
	{
		if (ft_atoi(str) < 0 || ft_atoi(str) > 1)
			err(RANGE_VECTOR);
		i++;
	}
}

void	check_range_color(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (str[i])
	{
		if (ft_atoi(split[i]) > 255 || ft_atoi(split[i]) < 0)
			err(COLOR_NOT_GOOD);
		i++;
	}
}

void	check_range_light(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while(split[i])
	{
		if (ft_atoi(str) < 0 || ft_atoi(str) > 1)
			err(RANGE_LIGHT);
		i++;
	}
}

void	check_range_numbers(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 1;
		while (block[i][j])
		{
			if (!strncmp(block[i][0], "A", 2))
			{
				check_range_light_ratio(block[i][1]);
				check_range_color(block[i][2]);
			}
			if (!ft_strncmp(block[i][0], "C"), 2)
			{
				check_range_vectors();
				check_range_fov();
			}
			j++;
		}
		i++;
	}
}
