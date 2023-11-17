/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:03:44 by motoko            #+#    #+#             */
/*   Updated: 2023/11/17 17:51:00 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_first_el(char ***block)
{
	int		i;
	int		j;
	int		is_found;
	char	**tab_char;
	char	**tab_string;

	i = -1;
	j = 0;
	is_found = 0;
	tab_char = (char *[]){"A", "C", "L", NULL};
	tab_string = (char *[]){"pl", "sp", "cy", NULL};
	while (block[++i])
	{
		j = 0;
		is_found = 0;
		while (tab_char[j] && tab_string[j])
		{
			if (!ft_strncmp(tab_char[j], block[i][0], 2) ||
					!ft_strncmp(tab_string[j], block[i][0], 3))
				is_found = 1;
			j++;
		}
		if (!is_found)
			err(INVALID_OBJECT);
	}
}

void	check_scene(char **tab)
{
	char	***block;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (tab[len])
		len++;
	block = malloc((len + 1) * sizeof(*block));
	while (tab[i])
	{
		block[i] = ft_split(tab[i], ' ');
		i++;
	}
	block[i] = NULL;
	check_first_el(block);
	check_num_objects(block);
	check_numbers(block);
	i = 0;
	while (block[i])
	{
		free_str_tab(block[i]);
		i++;
	}
	free(block);
}
