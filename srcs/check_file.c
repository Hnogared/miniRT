/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:21:46 by motoko            #+#    #+#             */
/*   Updated: 2023/11/10 15:35:51 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_file(char *scene)
{
	char	*file_type;

	file_type = ft_strrchr(scene, '.');
	if (!(!ft_strncmp(file_type, ".rt", 3) && ft_strlen(file_type) == 3))
		printf(FILE_NAME);
	return (0);
}
