/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_view_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:51:17 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 23:47:48 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Function to return a zero initialized t_ray structure with given vector and
 * origin coords.
 *
 * @param t_vector vector			-> orientation vector of the ray
 * @param t_coords origin_coords	-> coordinates from which the ray starts
 * @return t_ray					-> the newly initialized t_ray structure
 */
t_ray	new_ray(t_basis basis, t_coords origin_coords)
{
	t_ray	new;

	ft_bzero(&new, sizeof(t_ray));
	new.vector = basis.x;
	new.local_basis = basis;
	new.origin_coords = origin_coords;
	new.coords = origin_coords;
	return (new);
}

/*
 * Function to fill a pointed t_ray double pointer with rays which vectors and
 * coords are calculated from the given @param t_basis basis and @param t_object
 * camera.
 *
 * @param t_ray ***rays_tab	-> pointer to the t_ray double pointer to fill
 * @param int tab_sizes[2]	-> {width, height} sizes of the t_ray double pointer
 * @param t_basis basis		-> start basis from which to generate the rays
 * @param t_object camera	-> the camera from which to generate the rays
 *
 * @parent_func set_view_rays	-> function to allocate/generate a view's rays
 */
static void	set_rays_tab(t_ray ***rays_tab, const int tab_sizes[2],
	t_basis basis, t_object camera)
{
	int		x;
	int		y;
	float	angle[2];
	t_basis	first_basis;

	angle[0] = (float) camera.special_data.camera.h_fov / (tab_sizes[0] - 1);
	angle[1] = (float) camera.special_data.camera.v_fov / (tab_sizes[1] - 1);
	y = -1;
	while (++y < tab_sizes[1])
	{
		first_basis = basis;
		x = -1;
		while (++x < tab_sizes[0])
		{
			(*rays_tab)[y][x] = new_ray(basis, camera.coords);
			basis = axial_basis_rotation(basis, -angle[0],
					camera.local_basis.z);
		}
		basis = axial_basis_rotation(first_basis, angle[1], first_basis.y);
	}
}

/*
 * Function to allocate a pointed t_ray double pointer with given dimensions.
 *
 * @param t_ray ***rays_tab	-> pointer to the t_ray double pointer to allocate
 * @param int virtual_res[2]-> {width, height} array for the allocation sizes
 * @return int				-> status code [success/err/alloc_err]
 *
 * @parent_func set_view_rays	-> function to allocate/generate a view's rays
 */
static int	alloc_rays_tab(t_ray ***rays_tab, const int tab_sizes[2])
{
	int	i;

	if (!tab_sizes[0] || !tab_sizes[1])
		return (RTERR);
	(*rays_tab) = (t_ray **) ft_calloc(tab_sizes[1] + 1, sizeof(t_ray *));
	if (!(*rays_tab))
		return (errno);
	i = -1;
	while (++i < tab_sizes[1])
	{
		(*rays_tab)[i] = (t_ray *) ft_calloc(tab_sizes[0], sizeof(t_ray));
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
 * pointed t_ray double pointer with t_ray structures which vectors are
 * calculated from the @param t_window window and @param t_object camera data.
 * The window is used for the size of the double pointer (1 ray / virtual pixel)
 * and the camera's FOV is used to calculate the orientation of each ray.
 * The calculated rays are ready to be traced.
 *
 * @param t_ray ***rays_tab	-> pointer to the t_ray double pointer to alloc/fill
 * @param t_window window	-> window for which to generate the rays
 * @param t_object camera	-> camera through which to generate the rays
 * @param bool needs_alloc	-> true if @param t_ray ***rays_tab needs allocation 
 * @return int				-> status code [success/err/alloc_err]
 *
 * @child_func alloc_rays_tab	-> function to allocate the rays double pointer
 * @child_func set_rays_tab		-> function to fill the rays double pointer
 */
int	set_view_rays(t_ray ***rays_tab, t_window window, t_object camera,
	bool needs_alloc)
{
	int		virtual_res[2];
	t_basis	start_basis;
	int		i;

	if (!rays_tab)
		return (RTERR);
	virtual_res[0] = window.virtual_width;
	virtual_res[1] = window.virtual_height;
	i = 0;
	if (*rays_tab && needs_alloc == true)
	{
		while ((*rays_tab)[i])
			free((*rays_tab)[i++]);
		free(*rays_tab);
	}
	if ((needs_alloc == true || !(*rays_tab))
		&& alloc_rays_tab(rays_tab, virtual_res) != 0)
		return (errno);
	start_basis = axial_basis_rotation(camera.local_basis,
			(float) camera.special_data.camera.h_fov / 2, camera.local_basis.z);
	start_basis = axial_basis_rotation(start_basis,
			(float) -camera.special_data.camera.v_fov / 2, start_basis.y);
	set_rays_tab(rays_tab, virtual_res, start_basis, camera);
	return (0);
}

void	get_main_view_rays(t_data *data, bool needs_alloc)
{
	int	status;

	status = set_view_rays(&data->view_rays, data->render_window,
			*(data->active_camera), needs_alloc);
	if (status != 0)
	{
		status = ft_perror(NULL, data->error_tab, status);
		free_data(data);
		exit(status);
	}
}
