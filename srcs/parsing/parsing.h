/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:20:53 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 23:08:35 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* check_args.c */
int		check_num_objects(char ***block);

/* check_file.c */
int		check_file(char *scene);

/* check_numbers.c */
int		check_numbers(char ***block);

/* check_range_numbers.c */
int		check_range_numbers(char ***block);

/* check_range_numbers_2.c */
int		check_range_fov(char *fov);
int		check_range_vectors(char *str);
int		check_range_color(char *str);
int		check_range_light(char *str);

/* check_scene.c */
int		check_scene(t_data *data, char **tab);

/* get_file.c */
char	*get_file(const t_data *data, const char *scene);

/* init_objs.c */
int		initialize_object(t_data *data, char **tab);
void	obj_pl(unsigned int index, t_data *data, char *s, int *pos);
void	obj_sp(unsigned int index, t_data *data, char *s, int *pos);
void	obj_cy(unsigned int index, t_data *data, char *s, int *pos);

/* init_objs_2.c */
void	obj_a(t_data *data, char *s);
void	obj_c(unsigned int index, t_data *data, char *s, int *pos);
void	obj_l(unsigned int index, t_data *data, char *s, int *pos);

#endif
