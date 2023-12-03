/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:30:11 by motoko            #+#    #+#             */
/*   Updated: 2023/12/01 16:56:29 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*ft_free_and_join(char *stash, char *buf)
{
	char	*temp;

	temp = ft_strjoin(stash, buf);
	free(stash);
	return (temp);
}

char	*read_file(int fd)
{
	char	buf[BUFFER_SIZE];
	int		bytes_read;
	char	*str;

	bytes_read = 1;
	str = ft_calloc(1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		str = ft_free_and_join(str, buf);
		if (!str)
			return (NULL);
	}
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_file(t_data *data, char *scene)
{
	int		fd;
	char	*str;

	fd = open(scene, O_RDONLY);
	if (fd == -1)
		exit(ft_perror(NULL, data->error_tab, RTERR_OPEN_FILE));
	str = read_file(fd);
	if (!str)
		exit(ft_perror(NULL, data->error_tab, RTERR_OPEN_FILE));
	return (str);
}
