/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:53:48 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/09 18:05:07 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	rgb_to_sizet(t_rgb_color color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}

size_t	sizet_color_mix(size_t color1, size_t color2, float ratio)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	size_t			mask;

	mask = 0x0000FF;
	blue = ((mask & color1) + (mask & color2) * ratio) / 2;
	color1 >>= 8;
	color2 >>= 8;
	green = ((mask & color1) + (mask & color2) * ratio) / 2;
	color1 >>= 8;
	color2 >>= 8;
	red = ((mask & color1) + (mask & color2) * ratio) / 2;
	return (red << 16 | green << 8 | blue);
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
