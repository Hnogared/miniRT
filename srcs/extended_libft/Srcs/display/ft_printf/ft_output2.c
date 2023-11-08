/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:01:38 by hnogared          #+#    #+#             */
/*   Updated: 2023/06/06 22:52:11 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/libft.h"

int	ft_putnbr_fdout(int n, int len, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		len++;
		n *= -1;
	}
	if (n > 9)
	{
		len += ft_putnbr_fdout(n / 10, 0, fd);
		len += ft_putnbr_fdout(n % 10, 0, fd);
	}
	if (n <= 9)
	{
		ft_putchar_fdout(n + '0', fd);
		len++;
	}
	return (len);
}
