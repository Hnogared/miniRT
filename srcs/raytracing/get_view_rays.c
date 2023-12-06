/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_view_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/06 18:29:04 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_ray	new_ray(t_vector vector, t_coords origin_coords)
{
	t_ray	new;

	ft_bzero(&new, sizeof(t_ray));
	new.vector = vector;
	new.origin_coords = origin_coords;
	new.coords = origin_coords;
	return (new);
}

static t_ray	*set_vertical_rays(t_ray *rays_row, int v_virtual_res,
	t_basis basis, t_object camera)
{
	int			i;
	float		vertical_angle;

	if (!v_virtual_res)
		return (NULL);
	vertical_angle = (float) camera.special_data.camera.v_fov
		/ (v_virtual_res - 1);
	rays_row[0] = new_ray(basis.x, camera.coords);
	i = 1;
	while (i < v_virtual_res)
	{
		basis = axial_basis_rotation(basis, vertical_angle, basis.y);
		rays_row[i] = new_ray(basis.x, camera.coords);
		i++;
	}
	return (rays_row);
}

static t_ray	**set_rays_tab(t_ray ***rays_tab, int virtual_res[2],
	t_basis basis, t_object camera)
{
	int		i;
	float	horizontal_angle;

	horizontal_angle = (float) camera.special_data.camera.h_fov
		/ (virtual_res[0] - 1);
	i = 0;
	while (i < virtual_res[0])
	{
		set_vertical_rays((*rays_tab)[i++], virtual_res[1], basis, camera);
		basis = axial_basis_rotation(basis, 360.0f - horizontal_angle,
				camera.local_basis.z);
	}
	return (*rays_tab);
}

static t_ray	**alloc_rays_tab(t_ray ***rays_tab, int virtual_res[2])
{
	int	i;

	(*rays_tab) = (t_ray **) ft_calloc(virtual_res[0] + 1, sizeof(t_ray *));
	if (!(*rays_tab))
		return (NULL);
	i = -1;
	while (++i < virtual_res[0])
	{
		(*rays_tab)[i] = (t_ray *) ft_calloc(virtual_res[1], sizeof(t_ray));
		if ((*rays_tab)[i])
			continue ;
		while (i)
			free((*rays_tab)[--i]);
		free(*rays_tab);
		*rays_tab = NULL;
		break ;
	}
	return (*rays_tab);
}

t_ray	**set_view_rays(t_ray ***rays_tab, t_window window, t_object camera,
	bool needs_alloc)
{
	int		virtual_res[2];
	t_basis	start_basis;

	if (!rays_tab)
		return (NULL);
	virtual_res[0] = window.width / window.pixel_ratio;
	virtual_res[1] = window.height / window.pixel_ratio;
	if (needs_alloc == true || !(*rays_tab))
		alloc_rays_tab(rays_tab, virtual_res);
	start_basis = axial_basis_rotation(camera.local_basis,
			camera.special_data.camera.h_fov / 2, camera.local_basis.z);
	start_basis = axial_basis_rotation(start_basis,
			360 - camera.special_data.camera.v_fov / 2, start_basis.y);
	return (set_rays_tab(rays_tab, virtual_res, start_basis, camera));
}
