/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:30:11 by motoko            #+#    #+#             */
/*   Updated: 2024/01/06 23:01:54 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*ft_free_and_join(char *stash, char *buf)
{
	char	*temp;

	temp = ft_strjoin(stash, buf);
	free(stash);
	return (temp);
}

static char	*read_file(int fd)
{
	char	*line;
	char	*str;

	line = ft_strdup("#");
	while (line && line[0] == '#')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (NULL);
	str = line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '#')
			str = ft_free_and_join(str, line);
		free(line);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_file(const t_data *data, const char *scene)
{
	int		fd;
	char	*str;

	fd = open(scene, O_RDONLY);
	if (fd == -1)
		exit(ft_perror(NULL, data->error_tab, RTERR_OPEN_FILE));
	str = read_file(fd);
	close(fd);
	if (!str)
		exit(ft_perror(NULL, data->error_tab, RTERR_OPEN_FILE));
	return (str);
}
