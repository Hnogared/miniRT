/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:53:48 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/15 22:53:13 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return the smallest integer number between two @param numbers.
 *
 * @param int num1	-> first number to compare
 * @param int num2	-> second number to compare
 * @return int		-> the smallest number between the two parameters
 */
int	ft_min(int num1, int num2)
{
	return (num1 * (num1 <= num2) + num2 * (num2 < num1));
}

/*
 * Function to convert a t_rgb_color structure into an unsigned integer.
 *
 * @param t_rgb_color color	-> rgb color structure to convert
 * @return size_t			-> the corresponding unsigned int color
 */
size_t	rgb_to_sizet(t_rgb_color color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}

/*
 * Function to add a proportion of an rgb color to another one.
 * This effectively brightens up the color that is being added onto.
 *
 * @param t_rgb_color start_color	-> color structure to add onto
 * @param t_rgb_color add_color		-> color structure to add to the first one
 * @param float ratio				-> proportion of the @param add_color to add
 * @return t_rgb_color				-> the addition's resulting rgb color
 */
t_rgb_color	rgb_color_lighten(t_rgb_color start_color, t_rgb_color add_color,
	float ratio)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = ft_min((int)(start_color.red + (float) add_color.red * ratio), 255);
	green = ft_min((int)(start_color.green + (float) add_color.green * ratio), 255);
	blue = ft_min((int)(start_color.blue + (float) add_color.blue * ratio), 255);
	return ((t_rgb_color){red, green, blue});
}

/*
 * Function to mix/average out a proportion of an rgb color to another one.
 *
 * @param t_rgb_color start_color	-> color structure to mix with
 * @param t_rgb_color mix_color		-> color structure to mix with the first one
 * @param float ratio				-> proportion of the @param mix_color to mix
 * @return t_rgb_color				-> the mix resulting rgb color
 */
t_rgb_color	rgb_color_mix(t_rgb_color start_color, t_rgb_color mix_color,
	float ratio)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (start_color.red + (float) mix_color.red * ratio) / 2;
	green = (start_color.green + (float) mix_color.green * ratio) / 2;
	blue = (start_color.blue + (float) mix_color.blue * ratio) / 2;
	return ((t_rgb_color){red, green, blue});
}
