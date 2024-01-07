/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:03:44 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 18:06:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to check if all the objects names in the parameter block are valid.
 *
 * @param const char ***block	-> pointer to the objects data to check
 * @return int	-> true = 0 || false = RTERR_OBJ
 */
static int	check_first_el(const char ***block)
{
	int		i;
	int		j;
	int		is_found;
	char	**tab_char;
	char	**tab_string;

	i = -1;
	j = 0;
	tab_char = (char *[]){"A", "C", "L", NULL};
	tab_string = (char *[]){"pl", "sp", "cy", NULL};
	while (block[++i])
	{
		j = 0;
		is_found = 0;
		while (tab_char[j] && tab_string[j])
		{
			if (!ft_strncmp(tab_char[j], block[i][0], 2) ||
					!ft_strncmp(tab_string[j], block[i][0], 3))
				is_found = 1;
			j++;
		}
		if (!is_found)
			return (RTERR_OBJ);
	}
	return (0);
}

/*
 * Function to check if the objects and their data inside the parameter block
 * are valid.
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
 * @param const char ***block	-> pointer to the objects data to check
 * @return int	-> checks result
 */
static int	all_test(const t_data *data, const char ***block)
{
	int		status;

	status = 0;
	status = check_first_el(block);
	if (status)
		return (ft_perror(RTERR_MSG, data->error_tab, status));
	status = check_num_objects_args(block);
	if (status)
		return (ft_perror(RTERR_MSG, data->error_tab, status));
	status = check_numbers(block);
	if (status)
		return (ft_perror(RTERR_MSG, data->error_tab, status));
	status = check_range_numbers(block);
	if (status)
		return (ft_perror(RTERR_MSG, data->error_tab, status));
	return (0);
}

/*
 * Function to free the parameter objects data block.
 *
 * @param char ***block	-> pointer to the objects block to free
 */
static void	free_block(char ***block)
{
	char	***tmp;

	tmp = block;
	while (*tmp)
		free_double_pointer((void **) *(tmp++));
	free(block);
}

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
 * @param const char **tab		-> pointer to the strings array to check
 * @return int	-> checks result
 */
int	check_scene(const t_data *data, const char **tab)
{
	char	***block;
	int		i;
	int		len;
	int		status;

	i = 0;
	len = 0;
	status = 0;
	while (tab[len])
		len++;
	block = malloc((len + 1) * sizeof(*block));
	while (tab[i])
	{
		block[i] = ft_split_set(tab[i], " \t\n\v\f\r");
		i++;
	}
	block[i] = NULL;
	status = all_test(data, (const char ***) block);
	free_block(block);
	return (status);
}
