/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:57:36 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/05 22:00:17 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function to return the bigest of two floats.
 *
 * @param float n1	-> first float to compare
 * @param float n2	-> second float to compare
 * @return float	-> the bigest float
 */
float	ft_fmax(float n1, float n2)
{
	return (n1 * (n1 < n2) + n2 * (n1 >= n2));
}
