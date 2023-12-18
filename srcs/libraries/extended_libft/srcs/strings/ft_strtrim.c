/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:02:13 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 22:48:12 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkchr(const char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		len;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1) - 1;
	i = len;
	while (ft_checkchr(s1[i], set))
		i--;
	len -= len - ++i;
	i = 0;
	while (ft_checkchr(s1[i], set))
		i++;
	if (len)
		len -= i;
	trimmed = (char *) malloc(len * sizeof(char) + 1);
	if (!trimmed)
		return (NULL);
	j = 0;
	while (j < len)
		trimmed[j++] = s1[i++];
	trimmed[j] = 0;
	return (trimmed);
}
