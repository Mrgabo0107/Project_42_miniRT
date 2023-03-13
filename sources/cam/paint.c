/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:24:35 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/03 12:58:36 by ana              ###   ########.fr       */
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
	return (ret);
}

int	get_pixel_color(t_mrt *mrt, int x, int y)
{
	t_inter	inter;
	t_rgb	color;
	t_vec	dir;

	dir = normalize(vec_rest(screen_pxl_by_indx(&mrt->cam, x, y),
				mrt->cam.pos));
	inter = check_intersections(mrt, mrt->cam.pos, dir);
	if (inter.dist != -1)
		inter.norm = get_normal_at_point(mrt, inter);
	color = get_color(mrt, &inter, dir);
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
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
