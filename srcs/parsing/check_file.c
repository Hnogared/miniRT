/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:21:46 by motoko            #+#    #+#             */
/*   Updated: 2023/11/13 13:39:30 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_file(char *scene)
{
	char	*file_type;

	file_type = ft_strrchr(scene, '.');
	if (!file_type)
		err(FILE_NAME);
	if (!(!ft_strncmp(file_type, ".rt", 4)))
		err(FILE_NAME);
	return (0);
}
