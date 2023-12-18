/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:26:33 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:36:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*dup;

	str_len = ft_strlen(str);
	dup = (char *) malloc((str_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_memmove(dup, str, str_len * sizeof(char));
	dup[str_len] = 0;
	return (dup);
}
