/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:11:41 by tlorne            #+#    #+#             */
/*   Updated: 2023/11/10 15:11:42 by tlorne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc(sizeof(char) * (i + j + 1));
	if (str == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	free(s2);
	str[i + j] = 0;
	return (str);
}

int	change_hexa(int nb)
{
	char	*str;
	int		r;
	int		i;

	str = malloc(sizeof(char) * 3);
	r = nb % 16;
	i = 0;
	while (r)
	{
		if (r <= 9)
			str[i] = '0' + r;
		else
			str[i] = 'a' + r - 10;
		i++;
		nb = nb /16;
		r = nb % 16;
	}
	str[i] = 0;
	return (str);
}

char    add_col(char *fcolor, char color)
{
    int		col;
	char	*col_s;

	col = ft_atoi(color);
	col_s = change_hexa(col);
	fcolor = ft_strjoin_and_free(fcolor, col_s);
	return (fcolor);
}

char    *conv(t_rgb_color color)
{
    char *fcolor;

    fcolor = malloc(sizeof(char) * 5);
    fcolor[0] = '0';
    fcolor[1] = 'x';
    fcolor[2] = '0';
    fcolor[3] = '0';
    fcolor[4] = 0;
    fcolor = add_col(fcolor, color.red);
    fcolor = add_col(fcolor, color.green);
    fcolor = add_col(fcolor, color.blue);
	return (fcolor);
}
