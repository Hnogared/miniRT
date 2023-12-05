/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/05 15:43:22 by hnogared         ###   ########.fr       */
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

static t_ray	*get_vertical_rays(int v_virtual_res, int fov, t_basis basis,
	t_coords origin)
{
	int			i;
	float		vertical_angle;
	t_ray		*rays;

	if (!v_virtual_res)
		return (NULL);
	rays = (t_ray *) ft_calloc(v_virtual_res, sizeof(t_ray));
	if (!rays)
		return (NULL);
	vertical_angle = (float) fov / (v_virtual_res - 1);
	rays[0] = new_ray(basis.x, origin);
	i = 1;
	while (i < v_virtual_res)
	{
		basis = axial_basis_rotation(basis, vertical_angle, basis.y);
		rays[i] = new_ray(basis.x, origin);
		i++;
	}
	return (rays);
}

static t_ray	**get_rays_tab(int virtual_res[2], t_basis basis,
	t_object camera)
{
	int		i;
	float	horizontal_angle;
	t_ray	**rays_tab;

	rays_tab = (t_ray **) ft_calloc(virtual_res[0], sizeof(t_ray *));
	if (!rays_tab)
		return (NULL);
	horizontal_angle = (float) camera.special_data.camera.fov
		/ (virtual_res[0] - 1);
	i = 0;
	while (i < virtual_res[0])
	{
		rays_tab[i++] = get_vertical_rays(virtual_res[1], RT_VERTICAL_FOV,
				basis, camera.coords);
		if (!rays_tab[i - 1])
		{
			while (--i)
				free(rays_tab[i - 1]);
			free(rays_tab);
			return (NULL);
		}
		basis = axial_basis_rotation(basis, 360.0f - horizontal_angle,
				camera.local_basis.z);
	}
	return (rays_tab);
}

static t_basis	get_setup_basis(t_basis origin_basis, int fov)
{
	t_basis	new;

	new = axial_basis_rotation(origin_basis, fov / 2, origin_basis.z);
	new = axial_basis_rotation(new, 360 - RT_VERTICAL_FOV / 2, new.y);
	return (new);
}

t_ray	**get_view_rays(t_window window, t_object camera)
{
	int		virtual_res[2];
	t_basis	temp_basis;

	virtual_res[0] = window.width / window.pixel_ratio;
	virtual_res[1] = window.height / window.pixel_ratio;
	temp_basis = get_setup_basis(camera.local_basis,
			camera.special_data.camera.fov);
	return (get_rays_tab(virtual_res, temp_basis, camera));
}
