/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:46:14 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:28:06 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;
	char	*buffer_big;

	if (!big && !n)
		return (NULL);
	i = 0;
	buffer_big = (char *) big;
	if (little[0] == 0)
		return (buffer_big);
	while (buffer_big[i] && i < n)
	{
		j = 0;
		if (buffer_big[i] == little[0])
		{
			while (little[j] && i + j < n && buffer_big[i + j] == little[j])
				j++;
			if (little[j] == 0)
				return (buffer_big + i);
		}
		i++;
	}
	return (NULL);
}
