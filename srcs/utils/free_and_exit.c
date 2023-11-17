/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:25:22 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/16 10:25:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

noreturn int	free_and_exit(t_data *data)
{
	free_data(data);
	exit(0);
}

void	free_data(t_data *data)
{
	my_destroy_window(data->mlx_ptr, &data->main_window);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

void	free_str_tab(char **str_tab)
{
	char	**temp;

	temp = str_tab;
	while (*temp)
		free(*(temp++));
	free(str_tab);
}
