/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:43 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/31 16:42:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_triangle(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = mrt->triangle[inter.index].dir;
	// if (dot_prod(vec_rest(mrt->cam.pos, mrt->plane[inter.index].pos),
	// 		mrt->triangle[inter.index].dir) < 0.0)
	// 	ret = scal_vec(-1, ret);
	return (ret);
}

double	distance_to_triangle(t_vec start_point, t_triangle tri, t_vec ray)
{
	t_vec	tr_to_point;
	double	den;
	t_vec	e0;
	t_vec	e1;
	t_vec	e2;
	t_vec	c0;
	t_vec	c1;
	t_vec	c2;
	t_vec	p;
	double	c;

	e0 = vec_rest(tri.p2, tri.p1);
	e1 = vec_rest(tri.p3, tri.p2);
	e2 = vec_rest(tri.p1, tri.p3);
	den = dot_prod(tri.dir, ray);
	if (v_abs(den) > 0.001)
	{
		tr_to_point = vec_rest(tri.p1, start_point);
		c = dot_prod(tri.dir, tr_to_point) / den;
		p = vec_sum(start_point, scal_vec(c, ray));
		c0 = vec_rest(p, tri.p1);
		c1 = vec_rest(p, tri.p2);
		c2 = vec_rest(p, tri.p3);
		if (dot_prod(tri.dir, cross_prod(e0, c0)) > 0 && \
		dot_prod(tri.dir, cross_prod(e1, c1)) > 0 && \
		dot_prod(tri.dir, cross_prod(e2, c2)) > 0)
			return (c);
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

// void	*tri_thread(void *tri)
// {
// 	t_tri			*dat;
// 	t_triangle		triangle;
// 	t_vec			inter_coor;
// 	double			c;

// 	dat = (t_tri *)tri;
// 	triangle = dat->triangle;
// 	c = distance_to_triangle(dat->point, triangle, dat->dir);
// 	if (c > 0 && (dat->ctrl.dist == -1 || c < dat->ctrl.dist))
// 	{
// 		inter_coor = vec_sum(dat->point, scal_vec(c, dat->dir));
// 		dat->ctrl = (t_inter){TRIANGLE, dat->i, c, inter_coor, \
// 		fill_coord(0, 0, 0), triangle.color, \
// 		triangle.option, 0, 0};
// 	}
// 	return (NULL);
// }

// void	check_triangles(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
// {
// 	int		i;
// 	int		j;
// 	t_tri	dat;

// 	i = 0;
// 	j = 0;
// 	while (i < mrt->obj_count[TRIANGLE])
// 	{
// 		if (v_abs(dot_prod(mrt->triangle[i].dir, \
// 		vec_rest(dir, point))) < 0.0001)
// 			i++;
// 		else
// 		{
// 			dat = (t_tri){mrt->triangle[i], *ctrl, point, dir, i};
// 			pthread_create(&mrt->threads[i], NULL, tri_thread, (void *)&dat);
// 			i++;
// 			j++;
// 		}
// 	}
// 	i = 0;
// 	while (i < j)
// 	{
// 		pthread_join(mrt->threads[i], NULL);
// 		i++;
// 	}
// }

