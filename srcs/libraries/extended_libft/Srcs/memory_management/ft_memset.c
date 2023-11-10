/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:34:54 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:29:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = (char *) s;
	while (i < n)
		buffer[i++] = c;
	return ((void *) buffer);
}
