/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:00:54 by leudelin          #+#    #+#             */
/*   Updated: 2023/12/13 23:04:42 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_num_objects1(char	**block)
{
	int	i;

	i = 0;
	while (block[i])
		i++;
	if (i != 4)
		return (RTERR_OBJS_COUNT);
	return (0);
}

static int	check_num_objects2(char **block)
{
	int	i;

	i = 0;
	while (block[i])
		i++;
	if (i != 6)
		return (RTERR_OBJS_COUNT);
	return (0);
}

static int	check_num_objects3(char **block)
{
	int	i;

	i = 0;
	while (block[i])
		i++;
	if (i != 3)
		return (RTERR_OBJS_COUNT);
	return (0);
}

static int	all_test(char ***block, char **tab, char **tab1, int i)
{
	int	j;

	j = 0;
	while (block[i][j])
	{
		if (!ft_strncmp(block[i][j], tab[1], 2) ||
				(!ft_strncmp(block[i][j], tab[2], 2)))
			return (check_num_objects1(block[i]));
		if (!ft_strncmp(block[i][j], tab[0], 2))
			return (check_num_objects3(block[i]));
		if (!ft_strncmp(block[i][j], tab1[2], 3))
			return (check_num_objects2(block[i]));
		if (!ft_strncmp(block[i][j], tab1[0], 3) ||
				(!ft_strncmp(block[i][j], tab1[1], 3)))
			return (check_num_objects1(block[i]));
		j++;
	}
	return (0);
}

int	check_num_objects(char	***block)
{
	char	**tab;
	char	**tab1;
	int		i;
	int		status;

	i = 0;
	status = 0;
	tab = (char *[]){"A", "C", "L", NULL};
	tab1 = (char *[]){"pl", "sp", "cy", NULL};
	while (block[i])
	{
		status = all_test(block, tab, tab1, i);
		i++;
	}
	return (status);
}
