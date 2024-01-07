/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:20:53 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 15:34:08 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ************************************************************************** */
/* check_args.c                                                               */
/* ************************************************************************** */
/*
 * Function to check if all the objects in the parameter block each have the
 * valid number of arguments.
 *
 * @param const char ***block	-> pointer to the array of objects to test
 * @return int	-> true = 0 || false = RTERR_OBJS_ARGS
 */
int		check_num_objects_args(const char ***block);

/* ************************************************************************** */
/* check_file.c                                                               */
/* ************************************************************************** */
/*
 * Function to check if the parameter scene file path has the correct extension.
 *
 * @param const char *scene_file_path	-> string of the file path to check
 * @return int	-> true = 0 || false = -1
 */
int		check_file(const char *scene_file_path);

/* ************************************************************************** */
/* check_numbers.c                                                            */
/* ************************************************************************** */
int		check_numbers(const char ***block);

/* ************************************************************************** */
/* check_range_numbers.c                                                      */
/* ************************************************************************** */
int		check_range_numbers(const char ***block);

/* ************************************************************************** */
/* check_range_numbers_2.c                                                    */
/* ************************************************************************** */
int		check_range_fov(const char *fov);
int		check_range_vectors(const char *str);
int		check_range_color(const char *str);
int		check_range_light(const char *str);

/* ************************************************************************** */
/* check_scene.c                                                              */
/* ************************************************************************** */
int		check_scene(t_data *data, char **tab);

/* ************************************************************************** */
/* get_file.c                                                                 */
/* ************************************************************************** */
char	*get_file(const t_data *data, const char *scene);

/* ************************************************************************** */
/* init_objs.c                                                                */
/* ************************************************************************** */
int		initialize_object(t_data *data, char **tab);
void	obj_pl(unsigned int index, t_data *data, char *s, int *pos);
void	obj_sp(unsigned int index, t_data *data, char *s, int *pos);
void	obj_cy(unsigned int index, t_data *data, char *s, int *pos);

/* ************************************************************************** */
/* init_objs_2.c                                                              */
/* ************************************************************************** */
void	obj_a(t_data *data, char *s);
void	obj_c(unsigned int index, t_data *data, char *s, int *pos);
void	obj_l(unsigned int index, t_data *data, char *s, int *pos);

#endif
