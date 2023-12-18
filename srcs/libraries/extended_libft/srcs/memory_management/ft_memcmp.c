/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:16:32 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:59:58 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*buffer_s1;
	const unsigned char	*buffer_s2;

	buffer_s1 = s1;
	buffer_s2 = s2;
	while (n)
	{
		if (*buffer_s1 != *buffer_s2)
			return (*buffer_s1 - *buffer_s2);
		buffer_s1++;
		buffer_s2++;
		n--;
	}
	return (0);
}
