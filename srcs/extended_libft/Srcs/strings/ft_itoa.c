/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 08:23:55 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:32:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

static int	ft_get_nlen(int n)
{
	int	n_len;
	int	n_buffer;

	n_len = 0;
	n_buffer = n;
	if (n == 0)
		return (1);
	while (n_buffer)
	{
		n_buffer /= 10;
		n_len++;
	}
	if (n < 0)
		n_len++;
	return (n_len);
}

static char	*ft_make_nstr(char *str, int n, int len)
{
	int	i;

	i = 0;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	i = len - 1;
	while (n)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	str[len] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	*nstr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n_len = ft_get_nlen(n);
	nstr = (char *) malloc((n_len + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	return (ft_make_nstr(nstr, n, n_len));
}
