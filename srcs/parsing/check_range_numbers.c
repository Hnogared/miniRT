/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range_numbers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leudelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:47:33 by leudelin          #+#    #+#             */
/*   Updated: 2024/01/07 17:29:45 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
 */
static int	check_range_numbers_part1(const char **object)
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
		status = check_range_vectors(object[2]);
		if (status)
			return (status);
		status = check_range_fov(object[3]);
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
 */
static int	check_range_numbers_part2(const char **object)
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
	return (status);
}

/*
 * Function to check if the parameter strings array is plane or cylinder data, if
 * true check if its arguments are in valid ranges.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return 0 else.
 *
 * @param const char **object	-> pointer to the strings array to check
 * @return int	-> checks result 
 */
static int	check_range_numbers_part3(const char **object)
{
	int	status;

	status = 0;
	if (!ft_strncmp(object[0], "pl", 2))
	{
		status = check_range_vectors(object[2]);
		if (status)
			return (status);
		status = check_range_color(object[3]);
		if (status)
			return (status);
	}
	if (!strncmp(object[0], "cy", 3))
	{
		status = check_range_vectors(object[2]);
		if (status)
			return (status);
		status = check_range_color(object[5]);
		if (status)
			return (status);
	}
	return (status);
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
			status = check_range_numbers_part1(block[i]);
			if (status)
				return (status);
			status = check_range_numbers_part2(block[i]);
			if (status)
				return (status);
			status = check_range_numbers_part3(block[i]);
			if (status)
				return (status);
			j++;
		}
		i++;
	}
	return (0);
}
