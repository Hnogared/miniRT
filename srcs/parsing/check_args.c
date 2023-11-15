/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:00:54 by leudelin          #+#    #+#             */
/*   Updated: 2023/11/13 15:00:58 by leudelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	count_commas(char *block)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (block[i])
	{
		if (block[i] == 44)
			flags += 1;
		i++;
	}
	return (flags);
}

void	check_num_objects2(char ***block)
{
	char	**tab;
	int	j;

	tab = (char *[]) {"pl", "sp", "cy", NULL};
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (!ft_strncmp(block[i][j], tab[2], 3))
			{
				while (block[i][j])
					j++;
				if (j != 6)
					err(IS_NOT_NUMBER);
			}
			if (!ft_strncmp(block[i][j], tab[0], 3) || (!ft_strncmp(block[i][j], tab[1], 3)))
			{
				while (block[0][j])
					j++;
				if (j != 4)
					err(IS_NOT_NUMBER);
			}
			i++;
		}
	}
}


void	check_num_objects(char ***block)
{
	char	**tab;
	int	j;

	tab = (char *[]) {"A", "C", "L", NULL};
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (!ft_strncmp(block[i][j], tab[0], 2))
			{
				while (block[i][j])
					j++;
				if (j != 3)
					err(IS_NOT_NUMBER);
			}
			if (!ft_strncmp(block[i][j], tab[1], 2) || (!ft_strncmp(block[i][j], tab[2], 2)))
			{
				while (block[0][j])
					j++;
				if (j != 4)
					err(IS_NOT_NUMBER);
			}
			i++;
		}
	}
}

void	check_num_args(char ***block)
{
	int	i;
	int	j;
	int	flags;

	i = 0;
	flags = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (j == 3)
			{
				flags = count_commas(block[i][j]);
				if (flags > 2)
					err(IS_NOT_NUMBER);
			}
			j++;
		}
		i++;
	}
}