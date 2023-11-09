/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/09 17:41:11 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINI_RT_H 
# define MINI_RT_H

# define SYNTAX_ERROR 2

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "libft.h"

int	check_file(char *scene);

#endif
