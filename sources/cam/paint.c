/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:24:35 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/28 22:09:05 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_angle_between(t_vec v1, t_vec v2)
{
	float	angle;

	if (vect_norm(v1) == 0 || vect_norm(v2) == 0)
		return (0);
	angle = acos(dot_prod(v1, v2) / (vect_norm(v1) * vect_norm(v2)));
	return (angle);
}

uint	diminish_color(uint color, t_vec vec1, t_vec ldir, t_inter *lray)
{
	uint	r;
	uint	g;
	uint	b;
	float	angle;

	if (lray->dist < 0)
	{
		if (angle == PI)
			printf("oooh\n");
		angle = get_angle_between(vec1, ldir);
	}
	else
	{
		printf("hello\n");
		angle = PI;
	}
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	// printf("angle: %f, ratio %f\n", angle, angle / (PI));
	// printf("1: r: %d, g: %d, b: %d\n", r, g, b);
	// if (angle > PI - 0.1)
	// 	printf("angle: %f, ratio %f\n", angle, angle / (PI));
	r -= r * angle / (PI);
	g -= g * angle / (PI);
	b -= b * angle / (PI);
	// printf("2: r: %d, g: %d, b: %d\n", r, g, b);
	return ((r << 16) | (g << 8) | b);
}

static uint	get_color(t_mrt *mrt, t_inter *ctr)
{
	int		color;
	t_vec	ldir;
	t_inter	lray;
	double	len;

	color = 0x000000;
	lray = (t_inter){mrt->light.pos, UNDEFINED, 0, -1};
	if (ctr->dist != -1)
	{
		// lray->norm_vec = vec_rest(mrt->light.pos, ctr->inter_coor);
		// ldir = normalize(vec_rest(ctr->inter_coor, mrt->light.pos));
		ldir = normalize(vec_rest(mrt->light.pos, ctr->inter_coor));
		len = vect_norm(vec_rest(mrt->light.pos, ctr->inter_coor));
		check_spheres(mrt, mrt->light.pos, &lray, ldir);
		printf("len: %f, lray.dist: %f\n", len, lray.dist);
		// if (lray.dist > len + 0.001 || lray.dist < len - 0.001)
		// 	return (color);
		// printf("lray);
		if (ctr->type == SPHERE)
			color = mrt->sphere[ctr->index].color;
		if (ctr->type == CYLINDER)
			color = mrt->cylinder[ctr->index].color;
		if (ctr->type == PLANE)
			color = mrt->plane[ctr->index].color;
		color = diminish_color(color, ctr->norm_vec, ldir, &lray);
	}
	// if (color > 0)
		// printf("color: %d\n", color);
	return (color);
}

uint	get_pixel_color(t_mrt *mrt, int x, int y)
{
	t_inter	ctr_i;
	uint	ret;
	t_vec	dir;

	ctr_i = (t_inter){screen_pxl_by_indx(&mrt->cam, x, y), UNDEFINED, 0, -1};
	// ctr_i.pxl = screen_pxl_by_indx(&mrt->cam, x, y);
	// ctr_i.type = UNDEFINED;
	// ctr_i.index = 0;
	// ctr_i.dist = -1;
	dir = normalize(vec_sum(ctr_i.pxl, scal_vec(-1, mrt->cam.pos)));
	// lightdir = normalize(lray.pxl);
	check_planes(mrt, &ctr_i, dir);
	check_spheres(mrt, mrt->cam.pos, &ctr_i, dir);
	// check_spheres(mrt, &lray, normalize(lray.pxl));
	check_cylinders(mrt, &ctr_i, dir);
	ret = get_color(mrt, &ctr_i);
	return (ret);
}

void	pixel_calcul(t_mrt *mrt)
{
	int	i;
	int	j;

	i = 0;
	while (i < IX)
	{
		j = 0;
		while (j < IY - 1)
		{
			my_mlx_pixel_put(mrt, i, j, get_pixel_color(mrt, i + 1, j + 1));
			j++;
		}
	i++;
	}
}

void	my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color)
{
	char	*dst;

	dst = mrt->addr + (y * mrt->sizel + x * (mrt->bpp / 8));
	*(unsigned int *)dst = color;
}
