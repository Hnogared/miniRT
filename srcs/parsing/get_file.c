/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:30:11 by motoko            #+#    #+#             */
/*   Updated: 2024/01/07 18:25:20 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to concatenate two strings and free the first parameter one.
 *
 * @param char *stash		-> pointer to the first concatenation string to free
 * @param const char *buf	-> pointer to the second concatenation string
 * @return char *	-> pointer to the result of teh concatenation
 */
static char	*ft_free_and_join(char *stash, const char *buf)
{
	char	*temp;

	temp = ft_strjoin(stash, buf);
	free(stash);
	return (temp);
}

/*
 * Function to read the parameter fd line by line and return the concatenation
 * of all the lines which do not start with '#' (comment lines).
 * Return NULL if an error occured, else return the fd contents.
 *
 * @param int fd	-> file descriptor to read from
 * @return char *	-> pointer to the entire read concatenation if successfull
 */
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

/*
 * Function to open and save the contents of a parameter scene file.
 * The file is read line by line. Lines starting with '#' (comments) are ignored.
 * Print an error and return NULL if an error occured, else return the file
 * contents.
 *
 * @param const t_data *data			-> program data pointer (for ft_perror)
 * @param const char *scene_file_path	-> pointer to the file path to open
 * @return char *	-> pointer to the file contents if successfull
 */
char	*get_file(const t_data *data, const char *scene_file_path)
{
	int		fd;
	char	*str;

	fd = open(scene_file_path, O_RDONLY);
	if (fd == -1)
		exit(ft_perror(NULL, data->error_tab, RTERR_OPEN_FILE));
	str = read_file(fd);
	close(fd);
	if (!str)
		exit(ft_perror(NULL, data->error_tab, RTERR_OPEN_FILE));
	return (str);
}
