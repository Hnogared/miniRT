/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 14:05:11 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_object	object;

	if (argc == 2)
		check_file(argv[1]);
	ft_bzero(&object, sizeof(t_object));
	object.special_data.camera.fov = 2000;
	object.type = CAMERA_OBJ;
	object.data_print_func = &print_camera_data;
//	object.data_print_func(object.special_data);
	print_object_data(object);
	return (0);
}
