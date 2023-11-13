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

void	check_color(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
		{
			i++;
			continue;
		}
		
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
				check_color(block[i][2]);
			j++;
		}
		i++;
	}
}
