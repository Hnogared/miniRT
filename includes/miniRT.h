/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/10 09:50:40 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINI_RT_H 
# define MINI_RT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define SYNTAX_ERROR 2

int	check_file(char *scene);

#endif
