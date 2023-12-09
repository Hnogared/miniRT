/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:23:05 by motoko            #+#    #+#             */
/*   Updated: 2023/12/09 18:54:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	obj_a(t_data *data, char *s)
{
	char	**args;
	char	**color;

	args = ft_split(s, ' ');
	data->ambient_l.ratio = ft_atof(args[1]);
	color = ft_split(args[2], ',');
	data->ambient_l.color = (t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]),
		ft_atoi(color[2])};
	free_str_tab(color);
	free_str_tab(args);
}

void	obj_c(t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**vector;

	args = ft_split(s, ' ');
	coords = ft_split(args[1], ',');
	vector = ft_split(args[2], ',');
	new_camera(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])},
		ft_atoi(args[3]));
	set_object_orientation(&(data->scene_objects[*pos]),
		(t_vector){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	data->active_camera = &(data->scene_objects[*pos]);
	(*pos)++;
	free_str_tab(args);
	free_str_tab(coords);
	free_str_tab(vector);
}

void	obj_l(t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;

	args = ft_split(s, ' ');
	coords = ft_split(args[1], ',');
	new_light(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])},
		ft_atof(args[2]));
	(*pos)++;
	free_str_tab(args);
	free_str_tab(coords);
}
