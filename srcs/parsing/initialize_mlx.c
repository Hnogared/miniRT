/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:23:05 by motoko            #+#    #+#             */
/*   Updated: 2023/12/04 14:12:20 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (open_main_window(data, "miniRT"))
		return (2);
	data->test = 10;
	init_key_hooks(data);
	return (0);
}
