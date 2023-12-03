/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:03:44 by motoko            #+#    #+#             */
/*   Updated: 2023/12/03 13:01:40 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_first_el(char ***block)
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

int	all_test(t_data *data, char ***block)
{
	int		status;

	status = 0;
	status = check_first_el(block);
	if (status)
		return (ft_perror(RTERR_MSG, data->error_tab, status));
	status = check_num_objects(block);
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

int	check_scene(t_data *data, char **tab)
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
		block[i] = ft_split(tab[i], ' ');
		i++;
	}
	block[i] = NULL;
	status = all_test(data, block);
	free_block(block);
	return (status);
}
