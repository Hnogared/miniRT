/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:27:05 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:31:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*buffer;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	buffer = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ft_memcpy((void *) buffer, (const void *) s1, s1_len);
	ft_memcpy((void *) buffer + s1_len, (const void *) s2, s2_len);
	buffer[s1_len + s2_len] = 0;
	return (buffer);
}
