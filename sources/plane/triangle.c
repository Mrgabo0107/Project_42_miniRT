/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:43 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/05 01:18:59 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_triangle(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = mrt->triangle[inter.index].dir;
	return (ret);
}

double	distance_to_triangle(t_vec start_point, t_triangle tri, t_vec ray)
{
	t_vec	tr_to_point;
	double	t[2];
	t_vec	e[3];
	t_vec	c[3];
	t_vec	p;

	e[0] = vec_rest(tri.p2, tri.p1);
	e[1] = vec_rest(tri.p3, tri.p2);
	e[2] = vec_rest(tri.p1, tri.p3);
	t[0] = dot_prod(tri.dir, ray);
	if (v_abs(t[0]) > 0.001)
	{
		tr_to_point = vec_rest(tri.p1, start_point);
		t[1] = dot_prod(tri.dir, tr_to_point) / t[0];
		p = vec_sum(start_point, scal_vec(t[1], ray));
		c[0] = vec_rest(p, tri.p1);
		c[1] = vec_rest(p, tri.p2);
		c[2] = vec_rest(p, tri.p3);
		if (dot_prod(tri.dir, cross_prod(e[0], c[0])) > 0 && \
		dot_prod(tri.dir, cross_prod(e[1], c[1])) > 0 && \
		dot_prod(tri.dir, cross_prod(e[2], c[2])) > 0)
			return (t[1]);
	}
	return (-1);
}

void	check_triangles(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int		i;
	double	c;
	t_vec	inter_coor;

	i = 0;
	while (i < mrt->obj_count[TRIANGLE])
	{
		if (v_abs(dot_prod(mrt->triangle[i].dir, \
		vec_rest(dir, point))) < 0.0001)
			i++;
		else
		{
			c = distance_to_triangle(point, mrt->triangle[i], dir);
			if (c > 0 && (ctrl->dist == -1 || c < ctrl->dist))
			{
				inter_coor = vec_sum(point, scal_vec(c, dir));
				*ctrl = (t_inter){TRIANGLE, i, c, inter_coor, \
				fill_coord(0, 0, 0), mrt->triangle[i].color, \
				mrt->triangle[i].option, 0, 0};
			}
			i++;
		}
	}
}
