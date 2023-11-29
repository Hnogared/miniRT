/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:07:54 by motoko            #+#    #+#             */
/*   Updated: 2023/11/29 17:42:11 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	count_dot_and_comma(char *s, int *dot, int *comma)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	while (s[i])
	{
		(*dot) = 0;
		j = i;
		while (s[j] && s[j] != ',')
		{
			if (s[j] == '.')
				(*dot)++;
			j++;
		}
		if (s[j])
			(*comma)++;
		i = j + 1;
		if (i > (int)len)
			return ;
	}
}

void	check_dot_and_comma(t_data *data, char *s)
{
	int	dot;
	int	comma;

	dot = 0;
	comma = 0;
	count_dot_and_comma(s, &dot, &comma);
	if (dot > 1)
	{
		ft_perror(RTERR_MSG, data->error_tab, RTERR_NUM_DOT);
//		free_parsing_and_exit(data, block);
	}
	if (comma > 2)
	{
		ft_perror(RTERR_MSG, data->error_tab, RTERR_NUM_COMMA);
//		free_parsing_and_exit(data, block);
	}
}

void	check_begin_and_end(t_data *data, char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == ',' || s[len - 1] == '.')
	{
		ft_perror(RTERR_MSG, data->error_tab, RTERR_NUM);
//		free_parsing_and_exit(data, block);
	}
	if (s[0] == ',' || s[0] == '.')
	{
		ft_perror(RTERR_MSG, data->error_tab, RTERR_NUM);
//		free_parsing_and_exit(data, block);
	}
}

void	check_is_digit(t_data *data, char *s)
{
	int	i;

	i = -1;
	check_begin_and_end(data, s);
	check_dot_and_comma(data, s);
	while (s[++i])
	{
		if (i != 0 && ((s[i] == ',' || s[i] == '.'))
			&& ((s[i - 1] != ',' && s[i - 1] != '.')))
			continue ;
		if (i == 0 && !(ft_isdigit(s[i]) || s[i] == '-'))
		{
			ft_perror(RTERR_MSG, data->error_tab, RTERR_NUM);
//			free_parsing_and_exit(data, block);
		}
		if (i > 0 && (s[i - 1] && ((s[i - 1] == ',') && s[i] == '-')))
			continue ;
		if (i != 0 && !ft_isdigit(s[i]))
		{
			ft_perror(RTERR_MSG, data->error_tab, RTERR_NUM);
//			free_parsing_and_exit(data, block);
		}
	}
}

void	check_numbers(t_data *data, char ***block)
{
	int	i;
	int	j;
	int	is_present[3];

	i = 0;
	ft_bzero(is_present, 3 * sizeof(int));
	while (block[i])
	{
		j = 1;
		while (block[i][j])
		{
			check_is_digit(data, block[i][j]);
			j++;
		}
		if (!ft_strncmp(block[i][0], "A", 2))
			is_present[0] += 1;
		if (!ft_strncmp(block[i][0], "C", 2))
			is_present[1] += 1;
		if (!ft_strncmp(block[i][0], "L", 2))
			is_present[2] += 1;
		i++;
	}
	if (is_present[0] != 1 || is_present[1] != 1 || is_present[2] != 1)
	{
		ft_perror(RTERR_MSG, data->error_tab, RTERR_DUPLIC_OBJ);
//		free_parsing_and_exit(data, block);
	}
}
