/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:03:44 by motoko            #+#    #+#             */
/*   Updated: 2023/11/13 14:03:28 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_char(char ***block)
{
	int	i = 0;
	int	j = 0;

	char	**tab_char;
	char	**tab_string;

	tab_char = (char *[]) {"A", "C", "L", NULL};
	tab_string = (char *[]) {"pl", "sp", "cy", NULL};
	while (block[i])
	{
		j = 0;
		//if (!ft_isdigit(ft_atoi(block[i][0])))
		//	err(IS_NOT_NUMBER);
		while (tab_char[j] && tab_string[j])
		{
			if (!ft_strncmp(block[i][0], tab_char[j], 2))
				printf("%s\n", block[i][0]);
			if (!ft_strncmp(block[i][0], tab_string[j], 3))
				printf("%s\n", block[i][0]);
			j++;
		}
		printf("////////\n");
		i++;
	}
}

/*void	check_numbers(char ***block)
{
	int	i;

	i = 0;
	while (block[i])
	{

		printf("////////\n");
		i++;
	}
}*/

char	***check_scene(char **tab)
{
	char ***block;
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tab[len])
		len++;
	block = malloc(len * sizeof(block) + 1);
	while (tab[i])
	{
		block[i] = ft_split(tab[i], ' ');
		i++;
	}
	check_char(block);
	check_num_args(block);
	check_num_objects(block);
	//check_numbers(block);
	return (block);
}
