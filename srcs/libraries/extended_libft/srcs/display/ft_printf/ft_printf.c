/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:22:07 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 23:11:54 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_input(const char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1] == '%')
			i++;
		else if (input[i] == '%' && !ft_check_char(input[i + 1], "cspdiuxX"))
			return (ERROR);
		i++;
	}
	return (0);
}

int	ft_print_nbrconv(const char conv, va_list args, int fd)
{
	unsigned long	tempaddress;

	tempaddress = 0;
	if (conv == 'p')
	{
		tempaddress = (unsigned long) va_arg(args, unsigned long);
		if (!tempaddress)
			return (ft_putstr_fdout("(nil)", fd));
		return (ft_putstr_fdout("0x", fd)
			+ ft_puthex_fdout(tempaddress, 0, conv, fd));
	}
	if (conv == 'd' || conv == 'i')
		return (ft_putnbr_fdout((int) va_arg(args, int), 0, fd));
	if (conv == 'u')
		return (ft_putunsigned_fdout(va_arg(args, unsigned int), 0, fd));
	if (conv == 'x' || conv == 'X')
		return (ft_puthex_fdout(va_arg(args, unsigned int), 0, conv, fd));
	return (0);
}

int	ft_print_chrconv(const char conv, va_list args, int fd)
{
	int				count;
	char			*tempstr;

	count = 0;
	if (conv == 'c')
		count += ft_putchar_fdout((int) va_arg(args, int), fd);
	if (conv == 's')
	{
		tempstr = (char *) va_arg(args, char *);
		if (!tempstr)
			return (ft_putstr_fdout("(null)", fd));
		count += ft_putstr_fdout(tempstr, fd);
	}
	if (conv == '%')
		count += ft_putchar_fdout('%', fd);
	return (count);
}

int	ft_print_input(char *input, va_list args, int fd)
{
	int		count;
	size_t	i;
	size_t	j;

	i = 0;
	count = 0;
	while (input[i])
	{
		j = 0;
		while (input[i + j] && input[i + j] != '%')
			j++;
		write(fd, input + i, j);
		i += j;
		count += j;
		if (input[i] == '%')
		{
			if (ft_check_char(input[i + 1], "pdiuxX"))
				count += ft_print_nbrconv(input[i + 1], args, fd);
			if (ft_check_char(input[i + 1], "cs%"))
				count += ft_print_chrconv(input[i + 1], args, fd);
			i += 2;
		}
	}
	return (count);
}

int	ft_printf(const char *input, ...)
{
	int		count;
	va_list	args;

	count = 0;
	if (ft_check_input(input) == ERROR)
		return (0);
	va_start(args, input);
	count += ft_print_input((char *) input, args, STDOUT_FILENO);
	va_end(args);
	return (count);
}
