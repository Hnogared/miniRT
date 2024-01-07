/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/07 00:04:17 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdnoreturn.h>
# include <math.h>
# include <X11/Xlib.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# include "miniRT_macro.h"
# include "miniRT_struct.h"

# include "../srcs/basis/basis.h"
# include "../srcs/display/display.h"
# include "../srcs/object/object.h"
# include "../srcs/keyboard/keyboard.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/raytracing/raytracing.h"
# include "../srcs/vector/vector.h"

noreturn int	free_and_exit(t_data *data);
void			free_data(t_data *data);

#endif
