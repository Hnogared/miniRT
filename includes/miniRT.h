/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:09:56 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/09 19:32:03 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINI_RT_H 
# define MINI_RT_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# include "libft.h"

# define SYNTAX_ERROR 2

int	check_file(char *scene);

#endif
