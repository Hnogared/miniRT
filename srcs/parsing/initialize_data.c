/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:23:05 by motoko            #+#    #+#             */
/*   Updated: 2023/11/29 17:42:16 by hnogared         ###   ########.fr       */
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

int	initialize_data(t_data *data, char **tab)
{
	int	i;
	int	len;
	int	pos;
	
	i = 0;
	len = 0;
	pos = 0;
	ft_bzero(data, sizeof(t_data));
	while (tab[len])
		len++;
	data->scene_objects = (t_object *)ft_calloc(sizeof(t_object), len);	
	if (!data->scene_objects)
		return (3);
	data->obj_count = len;
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
	data->mlx_ptr = mlx_init();
	if (open_main_window(data, "miniRT"))
		return (2);
	data->test = 10;
	free(data->scene_objects);
	init_key_hooks(data);
	return (0);
}

