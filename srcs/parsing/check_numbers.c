/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:07:54 by motoko            #+#    #+#             */
/*   Updated: 2023/11/16 14:07:55 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_dot_and_comma(char *s)
{
	int	i;
	int	j;
	int	comma;
	int	dot;

	i = 0;
	j = 0;
	comma = 0;
	dot = 0;
	while (s[i])
	{
		dot = 0;
		j = i;
		while (s[j] && s[j] != ',')
		{
			if (s[j] == '.')
				dot++;
			j++;
		}
		if (dot > 1)
			err(TOO_MANY_DOT);
		if (s[j])
			comma++;
		if (comma > 2)
			err(TOO_MANY_COMMA);
		i = j + 1;
	}
}

void	check_begin_and_end(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == ',' || s[len - 1] == '.')
		err(IS_NOT_NUMBER);
	if (s[0] == ',' || s[0] == '.')
		err(IS_NOT_NUMBER);
}

void	check_is_digit(char *s)
{
	int	i;

	check_begin_and_end(s);
	i = 0;
	check_dot_and_comma(s);
	while (s[i])
	{
		if (i != 0 && ((s[i] == ',' || s[i] == '.'))
				&& ((s[i - 1] != ',' && s[i - 1] != '.')))
		{
			i++;
			continue;
		}
		if (i == 0 && !(ft_isdigit(s[i]) || s[i] == '-'))
				err(IS_NOT_NUMBER);
		if (s[i - 1] && ((s[i - 1] == ',') && s[i] == '-'))
		{
			i++;
			continue ;
		}
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
