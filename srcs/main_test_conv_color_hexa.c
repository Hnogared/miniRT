/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_conv_color_hexa.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/13 13:02:41 by tlorne           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char		*line;
	char		**tab;
	t_object	object;

	if (argc != 2)
		return (0);
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	check_scene(tab);

	new_sphere(&object, &(t_coords){1, 0, 10}, 1.0);
	set_object_color(&object, &(t_rgb_color){110, 0, 5});
	print_object_data(object);
	return (0);
}
