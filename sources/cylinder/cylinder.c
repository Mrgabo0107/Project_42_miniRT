/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/01 07:59:08 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// double	ft_cap(t_vec start_pos, t_cylinder cyl, t_vec ray, t_vec centre)
// {
// 	t_vec	plane_to_point;
// 	t_vec	intersect;
// 	double	den;
// 	double	c;

// 	den = dot_prod(cyl.dir, ray);
// 	if (v_abs(den) > 0.001)
// 	{
// 		plane_to_point = vec_rest(centre, start_pos);
// 		c = dot_prod(cyl.dir, plane_to_point) / den;
// 		intersect = vec_sum(start_pos, scal_vec(c, ray));
// 		if (vect_norm(vec_rest(intersect, centre)) <= cyl.radius && c > 0)
// 			return (c);
// 	}
// 	return (-1);
// }
// cas[1] = ft_cap(start_pos, cylinder, ray, cylinder.bottom);
// cas[0] = ft_cap(start_pos, cylinder, ray, cylinder.top);

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
	if (cas[0] < 0 || cas[1] < 0)
		return (max_v(cas[0], cas[1]));
	return (min_v(cas[0], cas[1]));
}

double	check_limits(t_mrt *mrt, t_cylinder cylinder, t_vec dir, t_discr discr)
{
	double	limit;
	double	dist;
	double	cap;

	cap = distance_to_cap(mrt->cam.pos, cylinder, dir);
	dist = (-discr.b - sqrt(discr.dscr)) / (2 * discr.a);
	limit = perp_to_plane(vec_sum(mrt->cam.pos, scal_vec(dist, dir)), \
	cylinder.pos, cylinder.dir);
	if (limit >= 0 && limit <= cylinder.height / 2)
	{
		if (cap >= 0 && dist >= 0)
			return (min_v(dist, cap));
		return (max_v(dist, cap));
	}
	dist = (-discr.b + sqrt(discr.dscr)) / (2 * discr.a);
	limit = perp_to_plane(vec_sum(mrt->cam.pos, scal_vec(dist, dir)), \
	cylinder.pos, cylinder.dir);
	if (limit >= 0 && limit <= cylinder.height / 2)
	{
		if (cap >= 0 && dist >= 0)
			return (min_v(dist, cap));
		return (max_v(dist, cap));
	}
	return (cap);
}

double	distance_to_cylinder(t_mrt *mrt, t_cylinder cyl, t_vec dir)
{
	t_vec	w;
	t_discr	discr;
	// double	t;
	// double	l;
	// double	c;

	w = vec_rest(mrt->cam.pos, cyl.pos);
	discr.a = dot_prod(dir, dir) - int_pow(dot_prod(dir, cyl.dir), 2);
	discr.b = 2 * (dot_prod(dir, w) - dot_prod(dir, cyl.dir) \
	* dot_prod(w, cyl.dir));
	discr.c = dot_prod(w, w) - int_pow(dot_prod(w, cyl.dir), 2) \
	- int_pow(cyl.radius, 2);
	discr.dscr = int_pow(discr.b, 2) - 4 * discr.a * discr.c;
	if (discr.dscr <= 0)
		return (-1);
	return (check_limits(mrt, cyl, dir, discr));
}

t_vec	norm_cylinder(t_cylinder cylinder, t_vec inter)
{
	t_vec	norm;
	t_vec	circle_to_inter;

	circle_to_inter = vec_rest(inter, cylinder.pos);
	norm = vec_rest(circle_to_inter, scal_vec(dot_prod(cylinder.dir, \
	circle_to_inter), cylinder.dir));
	return (norm);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec dir)
{
	int		i;
	double	c;
	t_vec	norm;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		c = distance_to_cylinder(mrt, mrt->cylinder[i], dir);
		if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			norm = norm_cylinder(mrt->cylinder[i], \
			vec_sum(mrt->cam.pos, scal_vec(c, dir)));
			*ctrl = (t_inter){CYLINDER, i, c, \
			vec_sum(mrt->cam.pos, scal_vec(c, dir)), fill_coord(0, 0, 0)};
		}
		i++;
	}
}
