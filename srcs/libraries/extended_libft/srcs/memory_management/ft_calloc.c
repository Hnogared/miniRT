/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:01:07 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:59:27 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	temp;
	void	*buffer;

	if (nmemb == 0 || size == 0)
		return ((void *) malloc(0));
	temp = nmemb * size;
	if (!(size == temp / nmemb))
		return (NULL);
	buffer = (void *) malloc(temp);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, temp);
	return (buffer);
}
