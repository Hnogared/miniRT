/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_view_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2023/12/07 12:08:57 by hnogared         ###   ########.fr       */
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

static void	set_horizontal_rays(t_ray *rays_line, int h_virtual_res,
	t_basis basis, t_object camera)
{
	int			i;
	float		horizontal_angle;

	horizontal_angle = (float) camera.special_data.camera.h_fov
		/ (h_virtual_res - 1);
	rays_line[0] = new_ray(basis.x, camera.coords);
	i = 1;
	while (i < h_virtual_res)
	{
		basis = axial_basis_rotation(basis, horizontal_angle,
				camera.local_basis.z);
		rays_line[i] = new_ray(basis.x, camera.coords);
		i++;
	}
}

static void	set_rays_tab(t_ray ***rays_tab, int virtual_res[2], t_basis basis,
	t_object camera)
{
	int		i;
	float	vertical_angle;

	vertical_angle = (float) camera.special_data.camera.v_fov
		/ (virtual_res[1] - 1);
	i = 0;
	while (i < virtual_res[1])
	{
		set_horizontal_rays((*rays_tab)[i++], virtual_res[0], basis, camera);
		basis = axial_basis_rotation(basis, vertical_angle, basis.y);
	}
}

/*
 *
 */
static int	alloc_rays_tab(t_ray ***rays_tab, int virtual_res[2])
{
	int	i;

	if (!virtual_res[0] || !virtual_res[1])
		return (RTERR);
	(*rays_tab) = (t_ray **) ft_calloc(virtual_res[1] + 1, sizeof(t_ray *));
	if (!(*rays_tab))
		return (errno);
	i = -1;
	while (++i < virtual_res[1])
	{
		(*rays_tab)[i] = (t_ray *) ft_calloc(virtual_res[0], sizeof(t_ray));
		if ((*rays_tab)[i])
			continue ;
		while (i)
			free((*rays_tab)[--i]);
		free(*rays_tab);
		*rays_tab = NULL;
		return (errno);
	}
	return (0);
}

/*
 * Function to allocate, if needed (@param bool needs_alloc), and fill a
 * pointed t_ray double array with t_ray structures which vectors are calculated
 * depending on the @param t_window window and @param t_object camera.
 * The window is used for the size of the double pointer (1 ray / virtual pixel)
 * and the camera's FOV is used to calculate the orientation of each ray.
 * The calculated rays are ready to be traced.
 *
 * @param t_ray ***rays_tab	-> pointer to the t_ray double pointer to alloc/fill
 * @param t_window window	-> window for which to generate the rays
 * @param t_object camera	-> camera through which to generate the rays
 * @param bool needs_alloc	-> true if @param t_ray ***rays_tab needs allocation 
 * @return int				-> status code of the function (succ/err/alloc_err)
 *
 * @child_func alloc_rays_tab	-> function to allocate the rays double pointer
 * @child_func set_rays_tab		-> function to fill the rays double pointer
 */
int	set_view_rays(t_ray ***rays_tab, t_window window, t_object camera,
	bool needs_alloc)
{
	int		virtual_res[2];
	t_basis	start_basis;

	if (!rays_tab)
		return (RTERR);
	virtual_res[0] = window.virtual_width;
	virtual_res[1] = window.virtual_height;
	if ((needs_alloc == true || !(*rays_tab))
		&& alloc_rays_tab(rays_tab, virtual_res) != 0)
		return (errno);
	start_basis = axial_basis_rotation(camera.local_basis,
			(float) camera.special_data.camera.h_fov / 2, camera.local_basis.z);
	start_basis = axial_basis_rotation(start_basis,
			360.0f - (float) camera.special_data.camera.v_fov / 2,
			start_basis.y);
	set_rays_tab(rays_tab, virtual_res, start_basis, camera);
	return (0);
}
