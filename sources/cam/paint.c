/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:24:35 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/23 19:01:47 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static uint	get_color(t_mrt *mrt, t_inter *ctr)
{
	if (ctr->dist != -1)
	{
		if (ctr->type == SPHERE)
			return (mrt->sphere[ctr->index].color);
		if (ctr->type == CYLINDER)
			return (mrt->cylinder[ctr->index].color);
		if (ctr->type == PLANE)
			return (mrt->plane[ctr->index].color);
	}
	return (0x000000);
}

uint	get_pixel_color(t_mrt *mrt, int x, int y)
{
	t_inter	ctr_i;
	uint	ret;

	ctr_i.type = UNDEFINED;
	ctr_i.index = 0;
	ctr_i.dist = -1;
	ctr_i.pxl = screen_pxl_by_indx(&mrt->cam, x, y);
	check_planes(mrt, &ctr_i);
	check_spheres(mrt, &ctr_i);
	// check_cylinders(mrt, &ctr_i);
	// printf("dist: %f\n", ctr_i.dist);
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
