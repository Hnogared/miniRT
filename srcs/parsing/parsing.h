/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:20:53 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 17:41:08 by hnogared         ###   ########.fr       */
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
/*
 * Function to check if the characters of all the arguments of the objects in the
 * parameter block are valid numbers and parameters.
 * Return RTERR_DUPLIC_OBJ if duplicate unique objects are present.
 * Return RTERR_NUM_DOT if one number has too many dots.
 * Return RTERR_NUM_COMMA if an argument has too many commas.
 * Return RTERR_NUM if a number or an argument is invalid.
 * Return 0 else.
 *
 * @param const char ***block	-> pointer to the objects array to check
 * @return int	-> checks result
 */
int		check_numbers(const char ***block);

/* ************************************************************************** */
/* check_range_numbers.c                                                      */
/* ************************************************************************** */
/*
 * Function to check if the numbers of all the arguments of the objects in the
 * parameter block are in valid ranges.
 * Return RTERR_BRIGHTNESS if brightness parameters are out of range.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return RTERR_FOV if FOV parameters are out of range.
 * Return 0 else.
 *
 * @param const char ***block	-> pointer to the objects + parameters to check
 * @return int	-> checks result
 */
int		check_range_numbers(const char ***block);

/* ************************************************************************** */
/* check_range_numbers_2.c                                                    */
/* ************************************************************************** */
/*
 * Function to check if the parameter string pointer contains an FOV in range.
 *
 * @param const char *fov	-> string pointer to check
 * @return int	-> true = 0 || false = RTERR_FOV
 */
int		check_range_fov(const char *fov);

/*
 * Function to check if the parameter string pointer contains a vector in range.
 *
 * @param const char *fov	-> string pointer to check
 * @return int	-> true = 0 || false = RTERR_VECTOR
 */
int		check_range_vector(const char *str);

/*
 * Function to check if the parameter string pointer contains a color in range.
 *
 * @param const char *fov	-> string pointer to check
 * @return int	-> true = 0 || false = RTERR_COLOR
 */
int		check_range_color(const char *str);

/*
 * Function to check if the parameter string pointer contains a light
 * brightness in range.
 *
 * @param const char *fov	-> string pointer to check
 * @return int	-> true = 0 || false = RTERR_BRIGTHNESS
 */
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
