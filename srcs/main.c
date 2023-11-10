/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 12:19:26 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_object	object;
//	t_data		data;

//	data.scene_objects = (t_object *) malloc(3 * sizeof(t_object));
	if (argc == 2)
		check_file(argv[1]);
	ft_bzero(&object, sizeof(t_object));
	object.light_data.brightness = 2000;
	object.type = SPHERE_OBJ;
//	printf("%d\n\n", sizeof(object), sizeof);
	print_object_data(object);
	return (0);
}
