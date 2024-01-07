/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:20:53 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 18:52:46 by hnogared         ###   ########.fr       */
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
/*
 * Function to split the lines inside the parameter tab and check if the
 * resulting objects and their parameters data are valid.
 * Displays an error message if an error is found.
 * Return RTERR_OBJ if an invalid object name is present.
 * Return RTERR_OBJS_ARGS if an object has an invalid numbers of arguments.
 * Return RTERR_DUPLIC_OBJ if duplicate unique objects are present.
 * Return RTERR_NUM_DOT if one number has too many dots.
 * Return RTERR_NUM_COMMA if an argument has too many commas.
 * Return RTERR_NUM if a number or an argument is invalid.
 * Return RTERR_BRIGHTNESS if brightness parameters are out of range.
 * Return RTERR_VECTOR if vector parameters are out of range.
 * Return RTERR_COLOR if color parameters are out of range.
 * Return RTERR_FOV if FOV parameters are out of range.
 * Return 0 else.
 *
 * @param const t_data *data	-> pointer to the program data (for ft_perror)
 * @param const char **tab		-> pointer to the strings array to split
 * @return int	-> checks result
 */
int		check_scene(const t_data *data, const char **tab);

/* ************************************************************************** */
/* get_file.c                                                                 */
/* ************************************************************************** */
/*
 * Function to open and save the contents of a parameter scene file.
 * The file is read line by line. Lines starting with '#' (comments) are ignored.
 * Print an error and return NULL if an error occured, else return the file
 * contents.
 *
 * @param const t_data *data			-> program data pointer (for ft_perror)
 * @param const char *scene_file_path	-> pointer to the file path to open
 * @return char *	-> pointer to the file contents if successfull
 */
char	*get_file(const t_data *data, const char *scene_file_path);

/* ************************************************************************** */
/* init_objs.c                                                                */
/* ************************************************************************** */
/*
 * Function to initialize a plane object using the parameter string pointer and
 * add it to the parameter data scene objects array.
 * The object arguments inside the parameter string can be separated by any
 * number of whitespaces and must be checked beforehand.
 *
 * @param unsigned int index	-> index of the new object
 * @param t_data *data			-> pointer to the program data to add into
 * @param const char *s			-> the object's arguments
 * @param int *pos				-> pointer to the last added object's array index
 */
void	obj_pl(unsigned int index, t_data *data, const char *s, int *pos);

/*
 * Function to initialize a sphere object using the parameter string pointer and
 * add it to the parameter data scene objects array.
 * The object arguments inside the parameter string can be separated by any
 * number of whitespaces and must be checked beforehand.
 *
 * @param unsigned int index	-> index of the new object
 * @param t_data *data			-> pointer to the program data to add into
 * @param const char *s			-> the object's arguments
 * @param int *pos				-> pointer to the last added object's array index
 */
void	obj_sp(unsigned int index, t_data *data, const char *s, int *pos);

/*
 * Function to initialize a cylinder object using the parameter string pointer
 * and add it to the parameter data scene objects array.
 * The object arguments inside the parameter string can be separated by any
 * number of whitespaces and must be checked beforehand.
 *
 * @param unsigned int index	-> index of the new object
 * @param t_data *data			-> pointer to the program data to add into
 * @param const char *s			-> the object's arguments
 * @param int *pos				-> pointer to the last added object's array index
 */
void	obj_cy(unsigned int index, t_data *data, const char *s, int *pos);

/*
 * Function to allocate and fill the pointed parameter data scene objects array
 * with the objects described inside the parameter strings array pointer.
 *
 * @param t_data *data		-> program data pointer updated with the new objects
 * @param const char **tab	-> pointer to the objects and their arguments array
 */
int		initialize_object(t_data *data, const char **tab);

/* ************************************************************************** */
/* init_objs_2.c                                                              */
/* ************************************************************************** */
/*
 * Function to initialize the scene ambient lighting using the parameter string
 * pointer and add it to the parameter data scene objects array.
 * The object arguments inside the parameter string can be separated by any
 * number of whitespaces and must be checked beforehand.
 *
 * @param unsigned int index	-> index of the new object
 * @param t_data *data			-> pointer to the program data to add into
 * @param const char *s			-> the object's arguments
 * @param int *pos				-> pointer to the last added object's array index
 */
void	obj_a(t_data *data, const char *s);

/*
 * Function to initialize a camera object using the parameter string pointer
 * and add it to the parameter data scene objects array.
 * The object arguments inside the parameter string can be separated by any
 * number of whitespaces and must be checked beforehand.
 * The initialized camera becomes the active camera of the parameter data.
 *
 * @param unsigned int index	-> index of the new object
 * @param t_data *data			-> pointer to the program data to add into
 * @param const char *s			-> the object's arguments
 * @param int *pos				-> pointer to the last added object's array index
 */
void	obj_c(unsigned int index, t_data *data, const char *s, int *pos);

/*
 * Function to initialize a light object using the parameter string pointer
 * and add it to the parameter data scene objects array.
 * The object arguments inside the parameter string can be separated by any
 * number of whitespaces and must be checked beforehand.
 *
 * @param unsigned int index	-> index of the new object
 * @param t_data *data			-> pointer to the program data to add into
 * @param const char *s			-> the object's arguments
 * @param int *pos				-> pointer to the last added object's array index
 */
void	obj_l(unsigned int index, t_data *data, const char *s, int *pos);

#endif
