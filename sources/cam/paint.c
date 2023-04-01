/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:24:35 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/01 21:12:52 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_copy_objects(t_mrt *mrt, t_mrt *dat)
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
		dat[i].mutex = mrt->mutex;
		dat[i].first = mrt->first;
		dat[i].scene_path = ft_strdup(mrt->scene_path);
		dat[i].obj_count = \
		ft_memcpy(mrt->obj_count, mrt->num_objs * sizeof(int));
		dat[i].num_objs = mrt->num_objs;
		dat[i].bounce = mrt->bounce;
		dat[i].ix = mrt->ix;
		dat[i].iy = mrt->iy;
		dat[i].amblight = mrt->amblight;
		dat[i].cam = mrt->cam;
		dat[i].percent = &mrt->i;
		ft_copy_objects(mrt, &dat[i]);
	}
	return (dat);
}

void	my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color)
{
	char	*dst;

	if (!mrt->save && x < BORDER)
		color = diminish_color(color, 0.3);
	dst = mrt->addr + (y * mrt->sizel + x * (mrt->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_percentage_bar(t_mrt *mrt)
{
	double	percent;
	int		i;

	i = -1;
	if (mrt->first)
	{
		pthread_mutex_lock(&mrt->mutex);
		percent = (double)*mrt->percent / (mrt->ix * THREADS) * 100;
		printf("\r[%.0f%%]", percent);
		(*mrt->percent)++;
		pthread_mutex_unlock(&mrt->mutex);
	}
}

void	*ft_paint(void *data)
{
	t_mrt	*mrt;
	int		i;
	int		j;
	int		color;

	mrt = (t_mrt *)data;
	i = 0;
	while (i < mrt->ix)
	{
		j = 0;
		ft_percentage_bar(mrt);
		while (j < mrt->iy - 1)
		{
			if (j % THREADS == mrt->i)
			{
				color = get_pixel_color(mrt, i + 1, j + 1);
				pthread_mutex_lock(&mrt->mutex);
				my_mlx_pixel_put(mrt, i, j, color);
				pthread_mutex_unlock(&mrt->mutex);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	pixel_calcul(t_mrt *mrt)
{
	int		i;
	t_mrt	*dat;

	i = 0;
	mrt->i = 0;
	dat = ft_copy_mrt(mrt, THREADS);
	while (i < THREADS)
	{
		dat[i].i = i;
		pthread_create(&mrt->threads[i], NULL, \
		(void *)ft_paint, (void *)&dat[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(mrt->threads[i], NULL);
		i++;
	}
	if (mrt->first)
		printf("\r[100%%]\n");
	ft_free(dat);
}
