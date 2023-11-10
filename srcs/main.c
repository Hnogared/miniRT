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

#include "miniRT.h"

int	main(void)
{
	t_rgb_color	test;

	test = malloc(sizeof(t_rgb_color) * 1);
	test.red = "255";
	test.blue = "255";
	test.green = "255";
	printf("la couleur vaut : %s", conv(test));
	return (0);
}
