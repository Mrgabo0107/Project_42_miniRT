/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bump_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:04:14 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/07 13:10:44 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bump_to_array(t_bump *bump_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	bump_map->array = ft_malloc(bump_map->height * sizeof(int *));
	while (i < bump_map->height)
	{
		bump_map->array[i] = ft_malloc(bump_map->width * sizeof(int));
		i++;
	}
	i = 0;
	while (i < bump_map->height)
	{
		while (j < bump_map->width)
		{
			bump_map->array[i][j] = \
			*(unsigned int *)(bump_map->addr + \
			(i * bump_map->sizel + j * (bump_map->bpp / 8)));
			j++;
		}
		j = 0;
		i++;
	}
}

void	set_bump_plane(t_mrt *mrt)
{
	int		i;
	t_bump	*bump_map;

	i = 0;
	while (i < mrt->obj_count[PLANE])
	{
		if (mrt->plane[i].option.bump_map.path)
		{
			bump_map = &mrt->plane[i].option.bump_map;
			bump_map->img = mlx_xpm_file_to_image(mrt->mlx, \
			bump_map->path, &bump_map->width, &bump_map->height);
			bump_map->addr = mlx_get_data_addr(bump_map->img, \
			&bump_map->bpp, &bump_map->sizel, &bump_map->endian);
			bump_to_array(bump_map);
			mlx_destroy_image(mrt->mlx, bump_map->img);
			bump_map->addr = NULL;
			bump_map->img = NULL;
		}
		i++;
	}
}

void	set_bump_sphere(t_mrt *mrt)
{
	int		i;
	t_bump	*bump_map;

	i = 0;
	while (i < mrt->obj_count[SPHERE])
	{
		if (mrt->sphere[i].option.bump_map.path)
		{
			bump_map = &mrt->sphere[i].option.bump_map;
			bump_map->img = mlx_xpm_file_to_image(mrt->mlx, \
			bump_map->path, &bump_map->width, &bump_map->height);
			bump_map->addr = mlx_get_data_addr(bump_map->img, \
			&bump_map->bpp, &bump_map->sizel, &bump_map->endian);
			bump_to_array(bump_map);
			mlx_destroy_image(mrt->mlx, bump_map->img);
			bump_map->addr = NULL;
			bump_map->img = NULL;
		}
		i++;
	}
}

void	set_bump_cylinder(t_mrt *mrt)
{
	int		i;
	t_bump	*bump_map;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		if (mrt->cylinder[i].option.bump_map.path)
		{
			bump_map = &mrt->cylinder[i].option.bump_map;
			bump_map->img = mlx_xpm_file_to_image(mrt->mlx, \
			bump_map->path, &bump_map->width, &bump_map->height);
			bump_map->addr = mlx_get_data_addr(bump_map->img, \
			&bump_map->bpp, &bump_map->sizel, &bump_map->endian);
			bump_to_array(bump_map);
			mlx_destroy_image(mrt->mlx, bump_map->img);
			bump_map->addr = NULL;
			bump_map->img = NULL;
		}
		i++;
	}
}

void	set_bump_maps(t_mrt *mrt)
{
	set_bump_plane(mrt);
	set_bump_sphere(mrt);
	set_bump_cylinder(mrt);
	// set_bump
}
