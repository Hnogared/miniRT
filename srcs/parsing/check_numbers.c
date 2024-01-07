/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:07:54 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 16:49:39 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to count the amount of commas in a string and check the amount of
 * dots between each pair of them.
 */
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
		if (i > (int)len || *dot > 1)
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
 * Function to check if there is one ambient lighting, one camera and one
 * (or any number if the bonus features are enabled) light pressent in the block.
 *
 * @param const char *obj_name	-> string name of the object to check
 * @param int is_present[3]		-> occurences array of each object to check
 * @return int	-> true = 0 || false = RTERR_DUPLIC_OBJ
 */
static int	check_is_present(const char *obj_name, int is_present[3])
{
	if (!ft_strncmp(obj_name, "A", 2))
		is_present[0] += 1;
	if (!ft_strncmp(obj_name, "C", 2))
		is_present[1] += 1;
	if (!ft_strncmp(obj_name, "L", 2))
		is_present[2] += 1;
	if (is_present[0] != 1 || is_present[1] != 1
		|| (RT_BONUS == 0 && is_present[2] != 1))
		return (RTERR_DUPLIC_OBJ);
	return (0);
}

/*
 * Function 
 */
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
		status = check_is_present(block[i][0], is_present);
		i++;
	}
	return (status);
}
