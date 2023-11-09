/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:22:07 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/09 17:57:38 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/libft.h"

int	ft_fprintf(int fd, const char *input, ...)
{
	int		count;
	va_list	args;

	count = 0;
	if (ft_check_input(input) == ERROR)
		return (0);
	va_start(args, input);
	count += ft_print_input((char *) input, args, fd);
	va_end(args);
	return (count);
}
