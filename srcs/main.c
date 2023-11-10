/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:21 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 17:23:40 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
//	t_object	object;
	char		*line;
	char		**tab;
	//char		***block;
//	t_data		data;

//	data.scene_objects = (t_object *) malloc(3 * sizeof(t_object));
	if (argc != 2)
		return (0);
	check_file(argv[1]);
	line = get_file(argv[1]);
	tab = ft_split(line, '\n');
	check_scene(tab);



//	ft_bzero(&object, sizeof(t_object));
//	object.light_data.brightness = 2000;
//	object.type = LIGHT_OBJ;
//	printf("%d\n\n", sizeof(object), sizeof);
//	print_object_data(object);
	return (0);
}
