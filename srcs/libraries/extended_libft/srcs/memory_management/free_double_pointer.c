/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_pointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:26:06 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 23:29:37 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_pointer(void **double_pointer)
{
	void	**temp;

	if (!double_pointer)
		return ;
	temp = double_pointer;
	while (*double_pointer)
		free(*(double_pointer++));
	free(temp);
}
