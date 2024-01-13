/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:09:58 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:59:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i > 0 && s[i] != (unsigned char) c)
		i--;
	return ((char *)((uintptr_t)(s + i) * (s[i] == (unsigned char) c)));
}
