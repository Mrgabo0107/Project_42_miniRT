/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:16:00 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/05 00:33:25 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_percentage_bar(t_mrt *mrt)
{
	double	percent;

	if (mrt->first)
	{
		pthread_mutex_lock(mrt->mutexs);
		percent = (double)*mrt->percent / (mrt->ix * THREADS) * 100;
		printf("\r[%.0f%%]", percent);
		(*mrt->percent)++;
		pthread_mutex_unlock(mrt->mutexs);
	}
}

int	**ft_copy_double_array(int height, int width, int **array)
{
	int	**new_array;
	int	i;

	i = 0;
	if (!array || !height || !width)
		return (NULL);
	new_array = (int **)ft_malloc(sizeof(int *) * height);
	while (i < height)
	{
		new_array[i] = (int *)ft_memcpy(array[i], width * sizeof(int));
		i++;
	}
	return (new_array);
}

void	ft_free_double_array(int **array, int height)
{
	int	i;

	i = 0;
	if (!array || !height)
		return ;
	while (i < height)
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}

void	ft_copy_bump_maps(t_mrt *mrt, t_mrt *dat)
{
	int	i;

	i = -1;
	while (++i < mrt->obj_count[SPHERE])
		dat->sphere[i].option.bump_map.array = \
		ft_copy_double_array(mrt->sphere[i].option.bump_map.height, \
		mrt->sphere[i].option.bump_map.width, \
		mrt->sphere[i].option.bump_map.array);
	i = -1;
	while (++i < mrt->obj_count[PLANE])
		dat->plane[i].option.bump_map.array = \
		ft_copy_double_array(mrt->plane[i].option.bump_map.height, \
		mrt->plane[i].option.bump_map.width, \
		mrt->plane[i].option.bump_map.array);
	i = -1;
	while (++i < mrt->obj_count[CYLINDER])
		dat->cylinder[i].option.bump_map.array = \
		ft_copy_double_array(mrt->cylinder[i].option.bump_map.height, \
		mrt->cylinder[i].option.bump_map.width, \
		mrt->cylinder[i].option.bump_map.array);
}

void	ft_free_bump_maps(t_mrt *mrt)
{
	int	i;

	i = -1;
	while (++i < mrt->obj_count[SPHERE])
		ft_free_double_array(mrt->sphere[i].option.bump_map.array, \
		mrt->sphere[i].option.bump_map.height);
	while (++i < mrt->obj_count[PLANE])
		ft_free_double_array(mrt->plane[i].option.bump_map.array, \
		mrt->plane[i].option.bump_map.height);
	while (++i < mrt->obj_count[CYLINDER])
		ft_free_double_array(mrt->cylinder[i].option.bump_map.array, \
		mrt->cylinder[i].option.bump_map.height);
}

void	ft_copy_mem(t_mrt *mrt, t_mrt *dat)
{
	dat->light = ft_memcpy(mrt->light, mrt->obj_count[LIGHT] * sizeof(t_light));
	dat->sphere = \
	ft_memcpy(mrt->sphere, mrt->obj_count[SPHERE] * sizeof(t_sphere));
	dat->plane = ft_memcpy(mrt->plane, mrt->obj_count[PLANE] * sizeof(t_plane));
	dat->cylinder = \
	ft_memcpy(mrt->cylinder, mrt->obj_count[CYLINDER] * sizeof(t_cylinder));
	dat->cone = ft_memcpy(mrt->cone, mrt->obj_count[CONE] * sizeof(t_cone));
	dat->triangle = \
	ft_memcpy(mrt->triangle, mrt->obj_count[TRIANGLE] * sizeof(t_triangle));
	dat->curr_obj = mrt->curr_obj;
	dat->scene_path = (mrt->scene_path);
	dat->obj_count = \
	ft_memcpy(mrt->obj_count, mrt->num_objs * sizeof(int));
	// ft_copy_bump_maps(mrt, dat);
}

t_mrt	*ft_copy_mrt(t_mrt *mrt, int num)
{
	int		i;
	t_mrt	*dat;

	i = -1;
	dat = ft_malloc(sizeof(t_mrt) * num);
	while (++i < num)
	{
		dat[i].save = mrt->save;
		dat[i].addr = mrt->addr;
		dat[i].bpp = mrt->bpp;
		dat[i].endi = mrt->endi;
		dat[i].sizel = mrt->sizel;
		dat[i].mutexs = &mrt->mutex;
		dat[i].first = mrt->first;
		dat[i].num_objs = mrt->num_objs;
		dat[i].bounce = mrt->bounce;
		dat[i].ix = mrt->ix;
		dat[i].iy = mrt->iy;
		dat[i].amblight = mrt->amblight;
		dat[i].cam = mrt->cam;
		dat[i].percent = &mrt->i;
		ft_copy_mem(mrt, &dat[i]);
	}
	return (dat);
}

void	ft_free_mrt(t_mrt *mrt, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		// ft_free_bump_maps(&mrt[i]);
		ft_free(mrt[i].light);
		ft_free(mrt[i].sphere);
		ft_free(mrt[i].plane);
		ft_free(mrt[i].cylinder);
		ft_free(mrt[i].cone);
		ft_free(mrt[i].triangle);
		ft_free(mrt[i].obj_count);
		ft_free(mrt[i].scene_path);
	}
	ft_free(mrt);
}
