/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 08:23:55 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/19 00:08:24 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function to get the amount of characters (digits and negative sign) inside
 * a number.
 *
 * @param int num	-> number to get the legth from
 * @return size_t	-> the resulting characters length
 *
 * @parent_func ft_itoab	-> function to store an int into a buffer string
 */
static size_t	get_num_len(int num)
{
	int		temp_num;
	size_t	num_len;

	num_len = 0;
	temp_num = num;
	while (temp_num)
	{
		temp_num /= 10;
		num_len++;
	}
	return (num_len + (num == 0) + (num < 0));
}

/*
 * Function to convert and store an integer inside a buffer array string.
 *
 * @param int n			-> the integer to store
 * @param char *buf		-> pointer to the array string to store the int into
 * @param size_t bufsize-> size in bytes of the buffer to store the int into
 * @return size_t		-> character size of the number saved inside the buffer
 *
 * @child_func get_num_len	-> function to get the character length of an int
 */
size_t	ft_itoab(int n, char *buf, size_t bufsize)
{
	int		i;
	size_t	num_len;

	if (!buf || !bufsize)
		return (0);
	if (n == -2147483648)
	{
		num_len = ft_min(11, bufsize - 1);
		ft_memmove(buf, "-2147483648", num_len * sizeof(char));
		buf[num_len] = 0;
		return (num_len);
	}
	num_len = ft_min(get_num_len(n), bufsize);
	buf[0] = '0' * (n == 0) + '-' * (n < 0);
	n *= 1 - 2 * (n < 0);
	i = num_len - 1;
	while (n && i > -1)
	{
		buf[i--] = (n % 10) + '0';
		n /= 10;
	}
	buf[num_len] = 0;
	return (num_len);
}
