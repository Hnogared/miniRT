/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:07:54 by motoko            #+#    #+#             */
/*   Updated: 2023/11/17 17:47:02 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	count_dot_and_comma(char *s, int *dot, int *comma)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	while (s[i])
	{
		(*dot) = 0;
		j = i;
		while (s[j] && s[j] != ',')
		{
			if (s[j] == '.')
				(*dot)++;
			j++;
		}
		if (s[j])
			(*comma)++;
		i = j + 1;
		if (i > (int)len)
			return ;
	}
}

void	check_dot_and_comma(char *s)
{
	int	dot;
	int	comma;

	dot = 0;
	comma = 0;
	count_dot_and_comma(s, &dot, &comma);
	if (dot > 1)
		err(TOO_MANY_DOT);
	if (comma > 2)
		err(TOO_MANY_COMMA);
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

	i = 0;
	check_begin_and_end(s);
	check_dot_and_comma(s);
	while (s[i])
	{
		if (i != 0 && ((s[i] == ',' || s[i] == '.'))
			&& ((s[i - 1] != ',' && s[i - 1] != '.')))
		{
			i++;
			continue ;
		}
		if (i == 0 && !(ft_isdigit(s[i]) || s[i] == '-'))
			err(IS_NOT_NUMBER);
		if (i > 0 && (s[i - 1] && ((s[i - 1] == ',') && s[i] == '-')))
		{
			i++;
			continue ;
		}
		if (i != 0 && !ft_isdigit(s[i]))
			err(IS_NOT_NUMBER);
		i++;
	}
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
		if (!ft_strncmp(block[i][0], "A", 2))
			is_present[0] += 1;
		if (!ft_strncmp(block[i][0], "C", 2))
			is_present[1] += 1;
		if (!ft_strncmp(block[i][0], "L", 2))
			is_present[2] += 1;
		i++;
	}
	if (is_present[0] != 1 || is_present[1] != 1 || is_present[2] != 1)
		err(DUPLICATE_OBJ);
}
