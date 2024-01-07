/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:21:46 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 15:33:40 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to check if the parameter scene file path has the correct extension.
 *
 * @param const char *scene_file_path	-> string of the file path to check
 * @return int	-> true = 0 || false = -1
 */
int	check_file(const char *scene_file_path)
{
	char	*file_extension;

	file_extension = ft_strrchr(scene_file_path, '.');
	if (!file_extension)
		return (-1);
	if (!(!ft_strncmp(file_extension, ".rt", 4)))
		return (-1);
	return (0);
}
