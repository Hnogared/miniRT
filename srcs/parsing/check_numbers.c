/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:07:54 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 16:04:56 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	count_dot_and_comma(const char *s, int *dot, int *comma)
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

static int	check_all(const char *s)
{
	int	dot;
	int	comma;
	int	len;

	dot = 0;
	comma = 0;
	len = ft_strlen(s);
	if (s[len - 1] == ',' || s[len - 1] == '.')
		return (RTERR_NUM);
	if (s[0] == ',' || s[0] == '.')
		return (RTERR_NUM);
	count_dot_and_comma(s, &dot, &comma);
	if (dot > 1)
		return (RTERR_NUM_DOT);
	if (comma > 2)
		return (RTERR_NUM_COMMA);
	return (0);
}

static int	check_is_digit(const char *s)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	status = check_all(s);
	if (status)
		return (status);
	while (s[++i])
	{
		if (i != 0 && ((s[i] == ',' || s[i] == '.'))
			&& ((s[i - 1] != ',' && s[i - 1] != '.')))
			continue ;
		if (i == 0 && !(ft_isdigit(s[i]) || s[i] == '-'))
			return (RTERR_NUM);
		if (i > 0 && (s[i - 1] && ((s[i - 1] == ',') && s[i] == '-')))
			continue ;
		if (i != 0 && !ft_isdigit(s[i]))
			return (RTERR_NUM);
	}
	return (0);
}

/*
 * Function to check if the ambient lighting and 
 */
static int	check_is_present(const char ***block, int is_present[3], int i)
{
	if (!ft_strncmp(block[i][0], "A", 2))
		is_present[0] += 1;
	if (!ft_strncmp(block[i][0], "C", 2))
		is_present[1] += 1;
	if (!ft_strncmp(block[i][0], "L", 2))
		is_present[2] += 1;
	if (is_present[0] != 1 || is_present[1] != 1
		|| (RT_BONUS == 0 && is_present[2] != 1))
		return (RTERR_DUPLIC_OBJ);
	return (0);
}

int	check_numbers(const char ***block)
{
	int	i;
	int	j;
	int	status;
	int	is_present[3];

	i = 0;
	status = 0;
	ft_bzero(is_present, 3 * sizeof(int));
	while (block[i])
	{
		j = 1;
		while (block[i][j])
		{
			status = check_is_digit(block[i][j]);
			if (status)
				return (status);
			j++;
		}
		status = check_is_present(block, is_present, i);
		i++;
	}
	return (status);
}
