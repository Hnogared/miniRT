/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:16:20 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/18 21:02:20 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function to check if a character is alphabetical [a-zA-Z].
 *
 * @param int c	-> character to check
 * @return int	-> 1 if true | 0 if false
 */
int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}
