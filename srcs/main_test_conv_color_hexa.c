/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/08 15:24:26 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "miniRT.h"
#include <stdio.h>


typedef struct s_rgb_color
{
	char	*red;
	char	*green;
	char	*blue;
}				t_rgb_color;

char    *conv(t_rgb_color color);

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	main(void)
{
	t_rgb_color	test;

	//test = malloc(sizeof(t_rgb_color) * 1);
	test.red = "56";
	test.green = "200";
	test.blue = "13";
	printf("la couleur vaut : %s\n", conv(test));
	return (0);
}
