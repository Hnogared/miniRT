/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:31:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:33:31 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*buffer;

	if (!s)
		return (NULL);
	i = 0;
	buffer = ft_strdup(s);
	if (!buffer)
		return (NULL);
	while (s[i])
	{
		buffer[i] = s[i];
		i++;
	}
	i = 0;
	while (buffer[i])
	{
		buffer[i] = (*f)(i, buffer[i]);
		i++;
	}
	return (buffer);
}
