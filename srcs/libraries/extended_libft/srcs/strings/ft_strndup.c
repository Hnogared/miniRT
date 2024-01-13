/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:02:15 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/13 23:29:11 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t size)
{
	size_t	i;
	size_t	len;
	char	*duped;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	len = size * (len > size) + len * (len <= size);
	duped = (char *) malloc((len + 1) * sizeof(char));
	if (!duped)
		return (NULL);
	i = 0;
	while (i < len)
	{
		duped[i] = str[i];
		i++;
	}
	duped[i] = 0;
	return (duped);
}
