/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:42:10 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 20:52:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function to check if a character is a number [0-9].
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
