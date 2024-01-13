/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 08:47:57 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:59:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buffer;

	buffer = (unsigned char *) s;
	while (n)
	{
		if (*buffer == (unsigned char) c)
			return ((void *) buffer);
		buffer++;
		n--;
	}
	return (NULL);
}
