/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 08:23:55 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 23:03:57 by hnogared         ###   ########.fr       */
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
 * @parent_func ft_itoa	-> function to convert an int into an allocated string
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
 * Function to convert an integer into an allocated string.
 *
 * @param int n		-> integer to convert
 * @return char *	-> the resulting allocated string
 *
 * @child_func get_num_len -> function to get the character length of an int
 */
char	*ft_itoa(int n)
{
	size_t	i;
	size_t	num_len;
	char	*num_str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num_len = get_num_len(n);
	num_str = (char *) malloc((num_len + 1) * sizeof(char));
	if (!num_str)
		return (NULL);
	num_str[0] = '0' * (n == 0) + '-' * (n < 0);
	n *= 1 - 2 * (n < 0);
	i = num_len - 1;
	while (n)
	{
		num_str[i--] = (n % 10) + '0';
		n /= 10;
	}
	num_str[num_len] = 0;
	return (num_str);
}
