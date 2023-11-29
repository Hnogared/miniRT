/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/11/29 17:27:30 by hnogared         ###   ########.fr       */
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

/*
 * TODO alloc error management
 */
static t_ray	*get_horizontal_rays(int h_virtual_res, int fov,
	t_orthonormal_basis basis, t_coords origin)
{
	int			i;
	float		horizontal_angle;
	t_vector	ray_vector;
	t_ray		*rays;

	if (!h_virtual_res)
		return (NULL);
	rays = (t_ray *) ft_calloc(h_virtual_res, sizeof(t_ray));
	if (!rays)
		return (NULL);
	horizontal_angle = fov / (h_virtual_res - 1);
	rays[h_virtual_res / 2] = new_ray(basis.x, origin);
	i = -1;
	while (++i < h_virtual_res / 2)
	{
		ray_vector = axial_vector_rotation(rays[h_virtual_res / 2 - i].vector,
				horizontal_angle, basis.z);
		rays[h_virtual_res / 2 - i - 1] = new_ray(ray_vector, origin);
		if (i == h_virtual_res / 2 - 1 && h_virtual_res % 2 == 0)
			break ;
		ray_vector = axial_vector_rotation(rays[h_virtual_res / 2 + i].vector,
				360 - horizontal_angle, basis.z);
		rays[h_virtual_res / 2 + i + 1] = new_ray(ray_vector, origin);
	}
	return (rays);
}

static t_orthonormal_basis	get_setup_basis(t_orthonormal_basis origin_basis,
	int virtual_res[2], int fov)
{
	float				horizontal_angle;
	t_orthonormal_basis	new;

	new = origin_basis;
	horizontal_angle = fov / (virtual_res[0] - 1);
	new = axial_basis_rotation(new, 315.0f, new.y);
	if (virtual_res[0] % 2 == 0)
		new = axial_basis_rotation(new, 360.0f - horizontal_angle / 2.0f, new.z);
	return (new);
}

t_ray	**get_rays_tab(int virtual_res[2], t_orthonormal_basis basis,
	t_object camera)
{
	int			i;
	int			j;
	float		vertical_angle;
	t_ray		**rays_tab;

	rays_tab = (t_ray **) ft_calloc(virtual_res[1], sizeof(t_ray *));
	if (!rays_tab)
		return (NULL);
	vertical_angle = 90.0f / (virtual_res[1] - 1);
	i = 0;
	while (i < virtual_res[1])
	{
		rays_tab[i] = get_horizontal_rays(virtual_res[0],
			camera.special_data.camera.fov, basis, camera.coords);
		if (!rays_tab[i])
			return (NULL);
		basis = axial_basis_rotation(basis, vertical_angle, camera.loc_basis.y);
		j = 0;
		while (j < virtual_res[0])
			print_vector(rays_tab[i][j++].vector);
		i++;
	}
	return (rays_tab);
}

/*
 * or view_rays maybe better idk
 */
int	camera_rays(t_data *data, t_object camera)
{
	int					virtual_res[2];
	t_ray				**rays_tab;
	t_orthonormal_basis	temp_basis;

	virtual_res[0] = data->main_window.width / data->pixel_ratio;
	virtual_res[1] = data->main_window.height / data->pixel_ratio;
	temp_basis = get_setup_basis(camera.loc_basis, virtual_res,
			camera.special_data.camera.fov);
	rays_tab = get_rays_tab(virtual_res, temp_basis, camera);
	free(rays_tab);
	return (0);
}
