/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:23:05 by motoko            #+#    #+#             */
/*   Updated: 2023/12/05 11:19:59 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	obj_pl(t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**vector;
	char	**color;

	args = ft_split(s, ' ');
	coords = ft_split(args[1], ',');
	vector = ft_split(args[2], ',');
	color = ft_split(args[3], ',');
	new_plane(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])});
	set_object_orientation(&(data->scene_objects[*pos]),
		(t_vector){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	set_object_color(&(data->scene_objects[*pos]),
		(t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])});
	(*pos)++;
	free_str_tab(args);
	free_str_tab(coords);
	free_str_tab(vector);
	free_str_tab(color);
}

void	obj_sp(t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**color;

	args = ft_split(s, ' ');
	coords = ft_split(args[1], ',');
	color = ft_split(args[3], ',');
	new_sphere(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])},
		ft_atof(args[2]));
	set_object_color(&(data->scene_objects[*pos]),
		(t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])});
	(*pos)++;
	free_str_tab(args);
	free_str_tab(coords);
	free_str_tab(color);
}

void	obj_cy(t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**vector;
	char	**color;

	args = ft_split(s, ' ');
	coords = ft_split(args[1], ',');
	vector = ft_split(args[2], ',');
	color = ft_split(args[5], ',');
	new_cylinder(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])},
		ft_atof(args[3]), ft_atof(args[4]));
	set_object_orientation(&(data->scene_objects[*pos]),
		(t_vector){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	set_object_color(&(data->scene_objects[*pos]),
		(t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])});
	(*pos)++;
	free_str_tab(args);
	free_str_tab(coords);
	free_str_tab(vector);
	free_str_tab(color);
}

void	exec_objs(t_data *data, char **tab)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'A')
			obj_a(data, tab[i]);
		if (tab[i][0] == 'C')
			obj_c(data, tab[i], &pos);
		if (tab[i][0] == 'L')
			obj_l(data, tab[i], &pos);
		if (!ft_strncmp(tab[i], "pl", 2))
			obj_pl(data, tab[i], &pos);
		if (!ft_strncmp(tab[i], "sp", 2))
			obj_sp(data, tab[i], &pos);
		if (!ft_strncmp(tab[i], "cy", 2))
			obj_cy(data, tab[i], &pos);
		i++;
	}
}

int	initialize_object(t_data *data, char **tab)
{
	int	len;

	len = 0;
	ft_bzero(data, sizeof(t_data));
	while (tab[len])
		len++;
	data->scene_objects = (t_object *)ft_calloc(sizeof(t_object), len - 1);
	if (!data->scene_objects)
		return (3);
	data->obj_count = len - 1;
	exec_objs(data, tab);
	return (0);
}
