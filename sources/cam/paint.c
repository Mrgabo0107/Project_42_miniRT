/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:24:35 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/31 16:38:45 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	check_intersections(t_mrt *mrt, t_vec point, t_vec dir)
{
	t_inter	ret;

	ret.type = UNDEFINED;
	ret.index = 0;
	ret.dist = -1;
	check_planes(mrt, &ret, point, dir);
	check_spheres(mrt, &ret, point, dir);
	check_cylinders(mrt, &ret, point, dir);
	check_triangles(mrt, &ret, point, dir);
	return (ret);
}

t_vec	get_normal_at_point(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = fill_coord(0, 0, 0);
	if (inter.type == PLANE)
		ret = get_normal_plane(mrt, inter);
	else if (inter.type == SPHERE)
		ret = get_normal_sphere(mrt, inter);
	else if (inter.type == CYLINDER)
		ret = get_normal_cylinder(mrt, inter);
	else if (inter.type == TRIANGLE)
		ret = get_normal_triangle(mrt, inter);
	return (ret);
}

int	get_pixel_color(t_mrt *mrt, int x, int y, t_vec dir)
{
	t_inter	inter;
	t_rgb	color;

	color = ft_make_rgb(0, 0, 0);
	inter = check_intersections(mrt, mrt->cam.pos, dir);
	if (inter.dist != -1)
	{
		inter.norm = get_normal_at_point(mrt, inter);
		color = get_object_color(mrt, &inter, dir, color);
		color = chosen_obj(mrt, x, y, color);
	}
	mrt->bounce = 0;
	color = normalize_color(color);
	color = show_light_sources(mrt, color, dir);
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

// void	*ft_paint(void *data)
// {
// 	t_mrt	*mrt;
// 	t_mrt	*dat;
// 	int		y;
// 	t_vec	dir;
// 	int		color;

// 	dat = (t_mrt *)data;
// 	pthread_mutex_lock(&dat->mutex);
// 	mrt = ft_memcpy(dat, sizeof(t_mrt));
// 	// printf("chess = %d\n", mrt->plane[0].option.chess_ctrl);
// 	// printf("mrt->x = %d\n", mrt->x);
// 	pthread_mutex_unlock(&dat->mutex);
// 	y = 0;
// 	while (y < mrt->iy - 1)
// 	{
// 		dir = normalize(vec_rest(screen_pxl_by_indx(mrt, \
// 		&mrt->cam, mrt->x + 1, y + 1), mrt->cam.pos));
// 		color = get_pixel_color(mrt, mrt->x + 1, y + 1, dir);
// 		pthread_mutex_lock(&dat->mutex);
// 		my_mlx_pixel_put(dat, mrt->x, y, color);
// 		pthread_mutex_unlock(&dat->mutex);
// 		y++;
// 	}
// 	return (NULL);
// }

// void	pixel_calcul(t_mrt *mrt)
// {
// 	int		i;
// 	// int		j;
// 	// int		color;
// 	// t_vec	dir;

// 	i = 0;
// 	while (i < mrt->ix)
// 	{
// 		mrt->x = i;
// 		// printf("mrt->x = %d\n", mrt->x);
// 		// printf("chess = %d\n", mrt->plane[0].option.chess_ctrl);
// 		pthread_create(&mrt->threads[i], NULL, \
// 		(void *)ft_paint, (void *)mrt);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < mrt->ix)
// 	{
// 		pthread_join(mrt->threads[i], NULL);
// 		i++;
// 	}
// }

t_mrt	*ft_copy_mrt(t_mrt *mrt, int num)
{
	int		i;
	t_mrt	*dat;

	i = 0;
	dat = ft_malloc(sizeof(t_mrt) * num);
	while (i < num)
	{
		dat[i].addr = mrt->addr;
		dat[i].mutex = mrt->mutex;
		dat[i].scene_path = ft_strdup(mrt->scene_path);
		dat[i].obj_count = \
		ft_memcpy(mrt->obj_count, mrt->num_objs * sizeof(int));
		dat[i].num_objs = mrt->num_objs;
		dat[i].bounce = mrt->bounce;
		dat[i].ix = mrt->ix;
		dat[i].iy = mrt->iy;
		dat[i].amblight = mrt->amblight;
		dat[i].cam = mrt->cam;
		dat[i].light = ft_memcpy(mrt->light, mrt->num_objs * sizeof(t_light));
		dat[i].sphere = \
		ft_memcpy(mrt->sphere, mrt->num_objs * sizeof(t_sphere));
		dat[i].plane = ft_memcpy(mrt->plane, mrt->num_objs * sizeof(t_plane));
		dat[i].cylinder = \
		ft_memcpy(mrt->cylinder, mrt->num_objs * sizeof(t_cylinder));
		dat[i].cone = ft_memcpy(mrt->cone, mrt->num_objs * sizeof(t_cone));
		dat[i].triangle = \
		ft_memcpy(mrt->triangle, mrt->num_objs * sizeof(t_triangle));
		dat[i].curr_obj = mrt->curr_obj;
		i++;
	}
	return (dat);
}

void	*ft_paint(void *data)
{
	t_mrt	*mrt;
	int		i;
	int		j;
	t_vec	dir;
	int		color;
	
	mrt = (t_mrt *)data;
	i = 0;
	while (i < mrt->ix)
	{
		j = 0;
		while (j < mrt->iy - 1)
		{
			if (j % THREADS == mrt->i)
			{
				dir = normalize(vec_rest(screen_pxl_by_indx(mrt, \
				&mrt->cam, i + 1, j + 1), mrt->cam.pos));
				color = get_pixel_color(mrt, i + 1, j + 1, dir);
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
	// int		j;
	// int		color;
	// t_vec	dir;
	t_mrt	*dat;

	i = 0;
	dat = ft_copy_mrt(mrt, THREADS);
	// printf("datplanecheck = %d\n", dat[2].plane[0].option.chess_ctrl);
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
	// while (i < mrt->ix)
	// {
	// 	j = 0;
	// 	while (j < mrt->iy - 1)
	// 	{
	// 		dir = normalize(vec_rest(screen_pxl_by_indx(mrt, \
	// 		&mrt->cam, i, j), mrt->cam.pos));
	// 		color = get_pixel_color(mrt, i + 1, j + 1, dir);
	// 		my_mlx_pixel_put(mrt, i, j, color);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

void	my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color)
{
	char	*dst;

	if (!mrt->save && x < BORDER)
		color = diminish_color(color, 0.3);
	dst = mrt->addr + (y * mrt->sizel + x * (mrt->bpp / 8));
	*(unsigned int *)dst = color;
}
