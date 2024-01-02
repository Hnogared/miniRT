/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:44:04 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 21:08:07 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	char	*iterator;

	if (!str)
		return (0);
	iterator = (char *) str;
	while (*iterator)
		iterator++;
	return (iterator - (char *) str);
}
