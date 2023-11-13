/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:03:44 by motoko            #+#    #+#             */
/*   Updated: 2023/11/13 17:18:25 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_char(char ***block)
{
	int	i = 0;
	int	j = 0;
	int	is_found = 0;

	char	**tab_char;
	char	**tab_string;

	tab_char = (char *[]) {"A", "C", "L", NULL};
	tab_string = (char *[]) {"pl", "sp", "cy", NULL};
	while (block[i])
	{
		j = 0;
		is_found = 0;
		while (tab_char[j] && tab_string[j])
		{
			if (!ft_strncmp(tab_char[j], block[i][0], 2))
				is_found = 1;	
			if (!ft_strncmp(tab_string[j], block[i][0], 2))
				is_found = 1;	
			j++;
		}
		if (!is_found)
			err(INVALID_OBJECT);
		i++;
	}
}

void	check_is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',' || s[i] == '.')
		{
			i++;
			continue;
		}
		if (i == 0 && !(ft_isdigit(s[i]) || s[i] == '-'))
				err(IS_NOT_NUMBER);
		if (i != 0 && !ft_isdigit(s[i]))
				err(IS_NOT_NUMBER);
		i++;
	}
}

void		check_duplicate_obj(char **block, int *is_present)
{
	if (!ft_strncmp(block[0], "A", 2))
		is_present[0] += 1;
	if (!ft_strncmp(block[0], "C", 2))
		is_present[1] += 1;
	if (!ft_strncmp(block[0], "L", 2))
		is_present[2] += 1;
}

void	check_numbers(char ***block)
{
	int	i;
	int	j;
	int	is_present[3];

	i = 0;
	ft_bzero(is_present, 3 * sizeof(int));
	while (block[i])
	{
		j = 1;
		while (block[i][j])
		{
			check_is_digit(block[i][j]);
			j++;
		}
		check_duplicate_obj(block[i], is_present);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (is_present[i] != 1)
			err(DUPLICATE_OBJ);
		i++;
	}
}

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
	check_numbers(block);
	return (block);
}

