/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:25:57 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 20:55:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function to change an alphabetical character to the lowercase.
 *
 * @param int c	-> character to change
 * @return int	-> the resulting character
 */
int	ft_tolower(int c)
{
	return (c + 32 * ('A' <= c && c <= 'Z'));
}
