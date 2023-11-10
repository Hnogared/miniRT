/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:03:44 by motoko            #+#    #+#             */
/*   Updated: 2023/11/10 18:02:11 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_char(char ***block)
{
	int	i = 0;
	int	j = 0;

	char	**tab_char;
	char	**tab_string;

	tab_char = ft_split("A C L", ' ');
	tab_string = ft_split("pl sp cy", ' ');
	while (block[i])
	{
		j = 0;
		while (tab_char[j])
		{
			if (!strcmp(block[i][0], tab_char[j]) && ft_strlen(block[i][0]) == 1)
				printf("%s\n", block[i][0]);
			j++;
		}
		j = 0;
		while (tab_string[j])
		{
			if (!strcmp(block[i][0], tab_string[j]) && ft_strlen(block[i][0]) == 2)
				printf("%s\n", block[i][0]);
			j++;
		}
		printf("////////\n");
		i++;
	}
}

char	***check_scene(char **tab)
{
	int	i;
	char ***block;

	i = 0;
	block = malloc(7 * sizeof(block));
	while (tab[i])
	{
		block[i] = ft_split(tab[i], ' ');
		i++;
	}
	check_char(block);
	return (block);
}
