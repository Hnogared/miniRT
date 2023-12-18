/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:39:40 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 21:04:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function to check if a character is displayable.
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int	ft_isprint(int c)
{
	return (' ' <= c && c <= '~');
}
