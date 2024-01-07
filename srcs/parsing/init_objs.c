/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:23:05 by motoko            #+#    #+#             */
/*   Updated: 2024/01/06 23:35:12 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	obj_pl(unsigned int index, t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**vector;
	char	**color;

	args = ft_split_set(s, " \t\n\v\f\r");
	coords = ft_split(args[1], ',');
	vector = ft_split(args[2], ',');
	color = ft_split(args[3], ',');
	new_plane(&(data->scene_objects[*pos]),
		(t_coords){ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2])});
	set_object_orientation(&(data->scene_objects[*pos]),
		(t_vector){ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2])});
	set_object_color(&(data->scene_objects[*pos]),
		(t_rgb_color){ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2])});
	data->scene_objects[*pos].id = index;
	(*pos)++;
	free_double_pointer((void **) args);
	free_double_pointer((void **) coords);
	free_double_pointer((void **) vector);
	free_double_pointer((void **) color);
}

void	obj_sp(unsigned int index, t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**color;

	args = ft_split_set(s, " \t\n\v\f\r");
	coords = ft_split(args[1], ',');
	color = ft_split(args[3], ',');
	new_sphere(&(data->scene_objects[*pos]),
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

void	obj_cy(unsigned int index, t_data *data, char *s, int *pos)
{
	char	**args;
	char	**coords;
	char	**vector;
	char	**color;

	args = ft_split_set(s, " \t\n\v\f\r");
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
	data->scene_objects[*pos].id = index;
	(*pos)++;
	free_double_pointer((void **) color);
	free_double_pointer((void **) vector);
	free_double_pointer((void **) coords);
	free_double_pointer((void **) args);
}

static void	exec_objs(t_data *data, char **tab)
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
			obj_c(i, data, tab[i], &pos);
		if (tab[i][0] == 'L')
			obj_l(i, data, tab[i], &pos);
		if (!ft_strncmp(tab[i], "pl", 2))
			obj_pl(i, data, tab[i], &pos);
		if (!ft_strncmp(tab[i], "sp", 2))
			obj_sp(i, data, tab[i], &pos);
		if (!ft_strncmp(tab[i], "cy", 2))
			obj_cy(i, data, tab[i], &pos);
		i++;
	}
}

int	initialize_object(t_data *data, char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	data->scene_objects = (t_object *)ft_calloc(sizeof(t_object), len - 1);
	if (!data->scene_objects)
		return (errno);
	data->obj_count = len - 1;
	exec_objs(data, tab);
	return (0);
}
