/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:03:43 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/13 23:02:39 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strndup(const char *str, size_t size)
{
	if (!size)
		return (NULL);
	return (ft_strndup(str, size));
}

char	*crop_buffer(char *buffer)
{
	char	*temp;

	temp = buffer;
	while (*temp && *temp != '\n')
		temp++;
	if (!*temp)
	{
		free(buffer);
		return (NULL);
	}
	temp = gnl_strndup(temp + 1, BUFFER_SIZE);
	free(buffer);
	return (temp);
}

char	*add_buffer(char *buffer, int fd, int *end)
{
	int		size;
	char	*temp;
	char	*temp2;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	size = 1;
	while (size && !*(ft_strchrnul(buffer, '\n')))
	{
		size = read(fd, temp, BUFFER_SIZE);
		if (size < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[size] = 0;
		temp2 = ft_strjoin(buffer, temp);
		free(buffer);
		buffer = temp2;
	}
	free(temp);
	if (!size)
		end[0] = 1;
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;

	if (!buffer || !*buffer)
		return (NULL);
	line = gnl_strndup(buffer, ft_strchr(buffer, '\n') - buffer + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	int			end;
	char		*line;
	static char	*buffer[1024];

	end = 0;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd])
		buffer[fd] = crop_buffer(buffer[fd]);
	if (!buffer[fd])
	{
		buffer[fd] = ft_calloc(1, sizeof(char));
		if (!buffer[fd])
			return (NULL);
	}
	buffer[fd] = add_buffer(buffer[fd], fd, &end);
	line = get_line(buffer[fd]);
	if ((end || read(fd, 0, 0) < 0) && buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
