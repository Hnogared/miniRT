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

void	check_num_objects1(char	**block)
{
	int	i;

	i = 0;
	while (block[i])
		i++;
	if (i != 4)
		err(TOO_MANY_OBJS);
}

void	check_num_objects2(char **block)
{
	int	i;

	i = 0;
	while (block[i])
		i++;
	if (i != 5)
		err(TOO_MANY_OBJS);
}

void	check_num_objects3(char **block)
{
	int	i;

	i = 0;
	while (block[i])
		i++;	
	if (i != 2)
		err(TOO_MANY_OBJS);
}

void	check_num_objects(char	***block)
{
	char	**tab;
	//char	**tab1;
	int		i;
	int		j;

	i = 0;
	tab = (char *[]) {"A", "C", "L", NULL};
	tab1 = (char *[]) {"pl", "sp", "cy", NULL};
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (!ft_strncmp(block[i][j], tab[1], 2) || (!ft_strncmp(block[i][j], tab[2], 2)))
				check_num_objects1(block[i]);
			if (!ft_strncmp(block[i][j], tab[0], 2))
				check_num_objects3(block[i]);
			if (!ft_strncmp(block[i][j], tab1[2], 3))
				check_num_objects2(block[i]);
			if (!ft_strncmp(block[i][j], tab1[0], 3) || (!ft_strncmp(block[i][j], tab1[1], 3)))
				check_num_objects1(block[i]);
			j++;
		}
		i++;
	}
}
