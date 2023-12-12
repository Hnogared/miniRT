/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:53:48 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/12 09:49:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_min(int num1, int num2)
{
	return (num1 * (num1 <= num2) + num2 * (num2 < num1));
}

size_t	rgb_to_sizet(t_rgb_color color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}

t_rgb_color	rgb_color_lighten(t_rgb_color color1, t_rgb_color color2,
	float ratio)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = ft_min(color1.red + (float) color2.red * ratio, 255);
	green = ft_min(color1.green + (float) color2.green * ratio, 255);
	blue = ft_min(color1.blue + (float) color2.blue * ratio, 255);
	return ((t_rgb_color){red, green, blue});
}

t_rgb_color	rgb_color_mix(t_rgb_color color1, t_rgb_color color2, float ratio)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (color1.red + (float) color2.red * ratio) / 2;
	green = (color1.green + (float) color2.green * ratio) / 2;
	blue = (color1.blue + (float) color2.blue * ratio) / 2;
	return ((t_rgb_color){red, green, blue});
}
