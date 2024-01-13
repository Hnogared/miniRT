/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:07:54 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 22:30:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to count the amount of commas in a string and check the amount of
 * dots between each pair of them.
 * If more than one dot is found between two commas, set *dot to 2 and return.
 *
 * @param const char *s	-> pointer to the string to check
 * @param int *dot		-> pointer to the counter to increment at each dot
 * @param int *comma	-> pointer to the counter to increment at each comma
 *
 * @parent_func check_all	-> function to check a number's commas/dots
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

/*
 * Function to check the number of commas and dots betw. two commas in a string.
 * Return RTERR_NUM if the parameter string starts/ends with a dot or a comma.
 * Return RTERR_NUM_DOT if more than one dots are present between two commas
 * Return RTERR_NUM_COMMA if more than two commas are present in the string
 * Return 0 else
 *
 * @param const char *s	-> pointer to the string to check
 * @return int	-> checks result
 *
 * @child_func count_dot_and_comma	-> function to count a string's commas/dots
 * @parent_func check_is_digit		-> function to check a string's numbers
 */
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

/*
 * Function to check if the characters between two commas in a string are
 * valid numbers.
 *
 * @param const char *s	-> pointer to the string to check
 * @return int	-> true = 0 || false = RTERR_NUM
 *
 * @child_func check_all		-> function to check a number's commas/dots
 * @parent_func check_numbers	-> function to check a block's numbers
 */
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
 *
 * @parent_func check_numbers	-> function to check a block's numbers
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
 * Function to check if the characters of all the arguments of the objects in the
 * parameter block are valid numbers and parameters.
 * Return RTERR_DUPLIC_OBJ if duplicate unique objects are present.
 * Return RTERR_NUM_DOT if one number has too many dots.
 * Return RTERR_NUM_COMMA if an argument has too many commas.
 * Return RTERR_NUM if a number or an argument is invalid.
 * Return 0 else.
 *
 * @param const char ***block	-> pointer to the objects array to check
 * @return int	-> checks result
 *
 * @child_func check_is_digit	-> function to check a string's numbers
 * @child_func check_is_present	-> function to check the amount of unique objs
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
