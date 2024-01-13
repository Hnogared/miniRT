/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:45:32 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:39:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (dest[dest_len] && dest_len < n)
		dest_len++;
	while ((i + dest_len) < (n - 1) && src[i])
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	if (i + dest_len < n)
		dest[i + dest_len] = 0;
	return (dest_len + ft_strlen(src));
}
