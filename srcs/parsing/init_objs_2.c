/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:23:05 by motoko            #+#    #+#             */
/*   Updated: 2024/01/06 23:35:32 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	obj_a(t_data *data, char *s)
{
	char	**args;
	char	**color;

	args = ft_split_set(s, " \t\n\v\f\r");
	data->ambient_l.ratio = ft_atof(args[1]);
	color = ft_split(args[2], ',');
	data->ambient_l.color = (t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]),
		ft_atoi(color[2])};
	free_double_pointer((void **) color);
	free_double_pointer((void **) args);
}

void	obj_c(unsigned int index, t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**vector;

	args = ft_split_set(s, " \t\n\v\f\r");
	coords = ft_split(args[1], ',');
	vector = ft_split(args[2], ',');
	new_camera(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])},
		ft_atoi(args[3]));
	set_object_orientation(&(data->scene_objects[*pos]),
		(t_vector){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	data->active_camera = &(data->scene_objects[*pos]);
	data->scene_objects[*pos].id = index;
	(*pos)++;
	free_double_pointer((void **) args);
	free_double_pointer((void **) coords);
	free_double_pointer((void **) vector);
}

void	obj_l(unsigned int index, t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**color;

	args = ft_split_set(s, " \t\n\v\f\r");
	coords = ft_split(args[1], ',');
	color = ft_split(args[3], ',');
	new_light(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])},
		ft_atof(args[2]));
	set_object_color(&(data->scene_objects[*pos]),
		(t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])});
	data->scene_objects[*pos].id = index;
	(*pos)++;
	free_double_pointer((void **) args);
	free_double_pointer((void **) coords);
	free_double_pointer((void **) color);
}
