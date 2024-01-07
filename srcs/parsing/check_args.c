/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:00:54 by leudelin          #+#    #+#             */
/*   Updated: 2024/01/07 15:34:45 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to check if the number of arguments for an object corresponds to
 * the parameter amount.
 *
 * @param const char **object_block	-> pointer to the object + arguments strings
 * @param size_t amount_to_check	-> amount of arguments to check for
 * @return int	-> true = 0 || false = RTERR_OBJS_ARGS
 */
static int	check_args_amount(const char **object_block, size_t amount_to_check)
{
	size_t	i;

	i = 0;
	while (object_block[i])
		i++;
	return (RTERR_OBJS_ARGS * (i != amount_to_check));
}

/*
 * Function to check if all the objects in the parameter block each have the
 * valid number of arguments.
 *
 * @param const char ***block	-> pointer to the array of objects to test
 * @return int	-> true = 0 || false = RTERR_OBJS_ARGS
 */
int	check_num_objects_args(const char ***block)
{
	char	**tab;
	char	**tab1;
	int		i;
	int		j;

	tab = (char *[]){"A", "C", "L", NULL};
	tab1 = (char *[]){"pl", "sp", "cy", NULL};
	i = -1;
	while (block[++i])
	{
		j = -1;
		while (block[i][++j])
		{
			if (!ft_strncmp(block[i][j], tab[1], 2)
					|| !ft_strncmp(block[i][j], tab[2], 2)
				|| !ft_strncmp(block[i][j], tab1[0], 3)
				|| !ft_strncmp(block[i][j], tab1[1], 3))
				return (check_args_amount(block[i], 4));
			if (!ft_strncmp(block[i][j], tab[0], 2))
				return (check_args_amount(block[i], 3));
			if (!ft_strncmp(block[i][j], tab1[2], 3))
				return (check_args_amount(block[i], 6));
		}
	}
	return (0);
}
