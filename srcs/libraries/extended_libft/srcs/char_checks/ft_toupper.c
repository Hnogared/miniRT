/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:15:00 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 20:56:36 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function to change an alphabetical character to the uppercase.
 *
 * @param int c	-> character to change
 * @return int	-> the resulting character
 */
int	ft_toupper(int c)
{
	return (c - 32 * ('a' <= c && c <= 'z'));
}
