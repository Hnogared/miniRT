/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:09:37 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 23:48:51 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

/* get_view_rays.c */
t_ray		new_ray(t_basis basis, t_coords origin_coords);
int			set_view_rays(t_ray ***rays_tab, t_window window, t_object camera,
				bool needs_alloc);
void		get_main_view_rays(t_data *data, bool needs_alloc);

/* raytrace.c */
size_t		test_grid(__attribute__((unused)) const t_data *data, int x, int y);
size_t		raytrace(const t_data *data, t_ray ray, bool anti_aliasing);

/* shadow_ray.c */
t_rgb_color	shadow_ray(t_coords start_coords, const t_object *objects_array,
				unsigned short objects_count, t_ambient_light ambient_l);

#endif
