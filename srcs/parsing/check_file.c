/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:21:46 by motoko            #+#    #+#             */
/*   Updated: 2023/12/01 16:39:37 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_file(char *scene)
{
	char	*file_type;

	file_type = ft_strrchr(scene, '.');
	if (!file_type)
		return (-1);
	if (!(!ft_strncmp(file_type, ".rt", 4)))
		return (-1);
	return (0);
}
