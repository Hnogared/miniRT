/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:47:33 by leudelin          #+#    #+#             */
/*   Updated: 2024/01/07 22:41:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to check if the parameter strings array is plane or cylinder data, if
 * true check if its arguments are in valid ranges.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return 0 else.
 *
 * @param const char **object	-> pointer to the strings array to check
 * @return int	-> checks result 
 *
 * @parent_func check_range_numbers_2	-> function to check L/sp ranges
 */
static int	check_range_numbers_3(const char **object)
{
	int	status;

	status = 0;
	if (!ft_strncmp(object[0], "pl", 2))
	{
		status = check_range_vector(object[2]);
		if (status)
			return (status);
		status = check_range_color(object[3]);
		if (status)
			return (status);
	}
	if (!strncmp(object[0], "cy", 3))
	{
		status = check_range_vector(object[2]);
		if (status)
			return (status);
		status = check_range_color(object[5]);
		if (status)
			return (status);
	}
	return (status);
}

/*
 * Function to check if the parameter strings array is light or sphere data, if
 * true check if its arguments are in valid ranges.
 * Return RTERR_BRIGHTNESS if brightness parameters are out of range.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return 0 else.
 *
 * @param const char **object	-> pointer to the strings array to check
 * @return int	-> checks result
 *
 * @child_func check_range_numbers_3	-> function to check pl/cy ranges
 * @parent_func check_range_numbers_1	-> function to check A/C ranges
 */
static int	check_range_numbers_2(const char **object)
{
	int	status;

	status = 0;
	if (!ft_strncmp(object[0], "L", 2))
	{
		status = check_range_light(object[2]);
		if (status)
			return (status);
		status = check_range_color(object[3]);
		if (status)
			return (status);
	}
	if (!strncmp(object[0], "sp", 3))
	{
		status = check_range_color(object[3]);
		if (status)
			return (status);
	}
	return (check_range_numbers_3(object));
}

/*
 * Function to check if the parameter strings array is ambient lighting or
 * camera data, if true check if its arguments are in valid ranges.
 * Return RTERR_BRIGHTNESS if brightness parameters are out of range.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return RTERR_FOV if FOV parameters are out of range.
 * Return 0 else.
 *
 * @param const char **object	-> pointer to the strings array to check
 * @return int	-> checks result
 *
 * @child_func check_range_numbers_2-> function to check L/sp ranges
 * @parent_func check_range_numbers	-> function to check the args' number ranges
 */
static int	check_range_numbers_1(const char **object)
{
	int	status;

	status = 0;
	if (!strncmp(object[0], "A", 2))
	{
		status = check_range_light(object[1]);
		if (status)
			return (status);
		status = check_range_color(object[2]);
		if (status)
			return (status);
	}
	if (!ft_strncmp(object[0], "C", 2))
	{
		status = check_range_vector(object[2]);
		if (status)
			return (status);
		status = check_range_fov(object[3]);
		if (status)
			return (status);
	}
	return (check_range_numbers_2(object));
}

/*
 * Function to check if the numbers of all the arguments of the objects in the
 * parameter block are in valid ranges.
 * Return RTERR_BRIGHTNESS if brightness parameters are out of range.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return RTERR_FOV if FOV parameters are out of range.
 * Return 0 else.
 *
 * @param const char ***block	-> pointer to the objects + parameters to check
 * @return int	-> checks result
 *
 * @child_func check_range_numbers_1	-> function to check A/C ranges
 */
int	check_range_numbers(const char ***block)
{
	int	i;
	int	j;
	int	status;

	status = 0;
	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			status = check_range_numbers_1(block[i]);
			if (status)
				return (status);
			j++;
		}
		i++;
	}
	return (0);
}
