/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 08:53:51 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:30:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*buffer_dest;
	char	*buffer_src;

	if (!dest && !src && n)
		return (NULL);
	i = 0;
	buffer_dest = (char *) dest;
	buffer_src = (char *) src;
	while (i < n)
	{
		buffer_dest[i] = buffer_src[i];
		i++;
	}
	return (dest);
}
