/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:29:46 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 23:01:21 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*buffer_dest;
	char	*buffer_src;

	if (!dest && !src && n)
		return (NULL);
	i = 0;
	buffer_dest = (char *) dest;
	buffer_src = (char *) src;
	if (src > dest)
	{
		while (i < n)
		{
			buffer_dest[i] = buffer_src[i];
			i++;
		}
		return (dest);
	}
	i = n - 1;
	while (i + 1 > 0)
	{
		buffer_dest[i] = buffer_src[i];
		i--;
	}
	return (dest);
}
