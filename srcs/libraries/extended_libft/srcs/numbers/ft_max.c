/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:57:36 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 21:58:30 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function to return the bigest of two integers.
 *
 * @param int n1	-> first integer to compare
 * @param int n2	-> second integer to compare
 * @return int		-> the bigest integer
 */
int	ft_max(int n1, int n2)
{
	return (n1 * (n1 > n2) + n2 * (n1 <= n2));
}
