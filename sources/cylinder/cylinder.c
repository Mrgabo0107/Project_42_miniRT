/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/05 21:32:07 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	distance_to_cap(t_vec start_pos, t_cylinder cyl, t_vec ray)
{
	double	cas[2];
	t_vec	plane_to_point;
	t_vec	intersect;
	double	den;
	double	c;

	den = dot_prod(cyl.dir, ray);
	if (v_abs(den) > 0.001)
	{
		plane_to_point = vec_rest(cyl.bottom, start_pos);
		c = dot_prod(cyl.dir, plane_to_point) / den;
		intersect = vec_sum(start_pos, scal_vec(c, ray));
		cas[0] = -1;
		if (vect_norm(vec_rest(intersect, cyl.bottom)) <= cyl.radius && c > 0)
			cas[0] = c;
		plane_to_point = vec_rest(cyl.top, start_pos);
		c = dot_prod(cyl.dir, plane_to_point) / den;
		intersect = vec_sum(start_pos, scal_vec(c, ray));
		cas[1] = -1;
		if (vect_norm(vec_rest(intersect, cyl.top)) <= cyl.radius && c > 0)
			cas[1] = c;
	}
	else
		return (-1);
	return (ft_max_valid(cas[0], cas[1]));
}

double	check_limits(t_vec point, t_cylinder cylinder, t_vec dir, t_discr discr)
{
	double	limit;
	double	dist;
	double	cap;

	cap = distance_to_cap(point, cylinder, dir);
	dist = (-discr.b - sqrt(discr.dscr)) / (2 * discr.a);
	limit = perp_to_plane(vec_sum(point, scal_vec(dist, dir)), \
	cylinder.pos, cylinder.dir);
	if (limit >= 0 && limit <= cylinder.height / 2)
		return (ft_max_valid(dist, cap));
	dist = (-discr.b + sqrt(discr.dscr)) / (2 * discr.a);
	limit = perp_to_plane(vec_sum(point, scal_vec(dist, dir)), \
	cylinder.pos, cylinder.dir);
	if (limit >= 0 && limit <= cylinder.height / 2)
		return (ft_max_valid(dist, cap));
	return (cap);
}

double	distance_to_cylinder(t_vec point, t_cylinder cyl, t_vec dir)
{
	t_vec	w;
	t_discr	discr;

	w = vec_rest(point, cyl.pos);
	discr.a = dot_prod(dir, dir) - int_pow(dot_prod(dir, cyl.dir), 2);
	discr.b = 2 * (dot_prod(dir, w) - dot_prod(dir, cyl.dir) \
	* dot_prod(w, cyl.dir));
	discr.c = dot_prod(w, w) - int_pow(dot_prod(w, cyl.dir), 2) \
	- int_pow(cyl.radius, 2);
	discr.dscr = int_pow(discr.b, 2) - 4 * discr.a * discr.c;
	if (discr.dscr <= 0)
		return (-1);
	return (check_limits(point, cyl, dir, discr));
}

t_vec	get_normal_cylinder(t_mrt *mrt, t_inter inter)
{
	t_vec	norm;
	t_vec	circle_to_inter;

	circle_to_inter = vec_rest(inter.inter_coor, \
	mrt->cylinder[inter.index].pos);
	if (vect_norm((vec_rest(inter.inter_coor, mrt->cylinder[inter.index].top))) \
	< mrt->cylinder[inter.index].radius || vect_norm(vec_rest(inter.inter_coor, \
	mrt->cylinder[inter.index].bottom)) < mrt->cylinder[inter.index].radius)
		return (mrt->cylinder[inter.index].dir);
	norm = vec_rest(circle_to_inter, \
	scal_vec(dot_prod(mrt->cylinder[inter.index].dir, \
	circle_to_inter), mrt->cylinder[inter.index].dir));
	return (norm);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int		i;
	double	c;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		c = distance_to_cylinder(point, mrt->cylinder[i], dir);
		if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			*ctrl = (t_inter){CYLINDER, i, c, vec_sum(mrt->cam.pos, \
			scal_vec(c, dir)), fill_coord(0, 0, 0), mrt->cylinder[i].color};
		}
		i++;
	}
}
