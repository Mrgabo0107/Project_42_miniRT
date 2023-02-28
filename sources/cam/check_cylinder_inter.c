/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_inter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/28 17:00:27 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_cap(t_mrt *mrt, t_cylinder cylinder, t_vec dir, t_vec pos)
{
	double	c;
	t_vec	circle_to_cam;
	t_vec	intersection;

	circle_to_cam = vec_rest(pos, mrt->cam.pos);
	c = v_abs(dot_prod(cylinder.dir, circle_to_cam) / dot_prod(cylinder.dir, dir));
	intersection = vec_sum(mrt->cam.pos, scal_vec(c, dir));
	if (vect_norm(vec_rest(intersection, pos)) > cylinder.radius)
		return (-1);
	return (c);
}

double	distance_to_cap(t_mrt *mrt, t_cylinder cylinder, t_vec dir)
{
	double	c[2];

	c[0] = ft_cap(mrt, cylinder, dir, cylinder.bottom);
	c[1] = ft_cap(mrt, cylinder, dir, cylinder.top);
	if (c[0] < 0 || c[1] < 0)
		return (max_v(c[0], c[1]));
	else
		return (min_v(c[0], c[1]));
}

double	distance_to_cylinder(t_mrt *mrt, t_cylinder cylinder, t_vec dir)
{
	t_vec	w;
	t_discr	discr;
	double	l[2];
	double	t[2];
	double	c;

	w = vec_rest(mrt->cam.pos, cylinder.pos);
	discr.a = dot_prod(dir, dir) - int_pow(dot_prod(dir, cylinder.dir), 2);
	discr.b = 2 * (dot_prod(dir, w) - dot_prod(dir, cylinder.dir) \
	* dot_prod(w, cylinder.dir));
	discr.c = dot_prod(w, w) - int_pow(dot_prod(w, cylinder.dir), 2) \
	- int_pow(cylinder.radius, 2);
	discr.dscr = int_pow(discr.b, 2) - 4 * discr.a * discr.c;
	if (discr.dscr <= 0)
		return (-1);
	t[0] = (-discr.b - sqrt(discr.dscr)) / (2 * discr.a);
	l[0] = perp_to_plane(vec_sum(mrt->cam.pos, scal_vec(t[0], dir)), \
	cylinder.pos, cylinder.dir);
	t[1] = (-discr.b + sqrt(discr.dscr)) / (2 * discr.a);
	l[1] = perp_to_plane(vec_sum(mrt->cam.pos, scal_vec(t[1], dir)), \
	cylinder.pos, cylinder.dir);
	if (l[0] >= 0 && l[0] <= cylinder.height / 2)
	{
		c = distance_to_cap(mrt, cylinder, dir);
		if (c >= 0 && t[0] >= 0)
			return (min_v(t[0], c));
		return (max_v(t[0], c));
		// return (t[0]);
	}
	if (l[1] >= 0 && l[1] <= cylinder.height / 2)
	{
		c = distance_to_cap(mrt, cylinder, dir);
		if (c >= 0 && t[1] >= 0)
			return (min_v(t[1], c));
		return (max_v(t[1], c));
		// return (t[1]);
	}
	return (-1);
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
			*ctrl = (t_inter){ctrl->pxl, CYLINDER, i, c, \
			vec_sum(mrt->cam.pos, scal_vec(c, dir)), norm};
		}
		i++;
	}
}

// double	distance_to_cylinder(t_mrt *mrt, t_cylinder cylinder, t_vec dir)
// {
// 	double	c;
// 	t_vec	cylinder_to_cam;
// 	t_vec	proj;
// 	t_vec	proj_to_cam;
// 	double	proj_len;

// 	cylinder_to_cam = vec_rest(cylinder.pos, mrt->cam.pos);
// 	proj = scal_vec(dot_prod(cylinder.dir, cylinder_to_cam), cylinder.dir);
// 	proj_to_cam = vec_rest(cylinder_to_cam, proj);
// 	proj_len = vect_norm(proj);
// 	c = dot_prod(cylinder.dir, proj_to_cam) / dot_prod(cylinder.dir, dir);
// 	if (c > 0)
// 		printf("proj_len = %f, c = %f\n", proj_len, c);
// 	if (proj_len > cylinder.radius)
// 		return (-1);
// 	return (c);
// }
// {
// 	double	c;

// 	c = vect_norm(cross_prod(dir, cylinder.dir)) / vect_norm(cylinder.dir);
// 	return (c);
// }
// {
// 	double	c;
// 	double	l;
// 	double		t[2];
// 	t_discr	discr;
// 	// c = -dot_prod() / pow(vect_norm(vec_rest(cylinder.top, )), 2);

// 	discr.a = pow(vect_norm(dir), 2) - pow(dot_prod(dir, cylinder.dir), 2);
// 	discr.b = 2 * (dot_prod(dir, vec_rest(mrt->cam.pos, cylinder.pos)) - 
// 		dot_prod(dir, cylinder.dir) * dot_prod(vec_rest(mrt->cam.pos, 
//cylinder.pos), cylinder.dir));
// 	discr.c = pow(vect_norm(vec_rest(mrt->cam.pos, cylinder.pos)), 2) - 
// 		pow(dot_prod(vec_rest(mrt->cam.pos, cylinder.pos), cylinder.dir), 2) - 
// 		pow(cylinder.radius, 2);
// 	discr.dscr = pow(discr.b, 2) - 4 * discr.a * discr.c;
// 	if (discr.dscr < 0)
// 		return (-1);
// 	t[0] = (-discr.b + sqrt(discr.dscr)) / (2 * discr.a);
// 	t[1] = (-discr.b - sqrt(discr.dscr)) / (2 * discr.a);
// 	if (t[0] > 0 && t[1] > 0)
// 	{
// 		// if (is_in(t[0], t) && is_in(t[1], t))
// 		// 	c = t[1];
// 		// else if (is_in(t[0], t))
// 		// 	c = t[1];
// 		// else if (is_in(t[1], t))
// 		// 	c = t[0];
// 		// else
// 		// 	c = t[1];
// 		c = t[1];
// 	}
// 	// else if (t[0] > 0)
// 	// 	c = t[0];
// 	// else if (t[1] > 0)
// 	// 	c = t[1];
// 	l = dot_prod(vec_sum(mrt->cam.pos, scal_vec(c, dir)), cylinder.dir);
// 	if (l >= 0 && l <= vect_norm(vec_rest(cylinder.top, cylinder.pos)))
// 		return (c);
// 	if (l < 0)
// 		return (ft_cap(mrt, cylinder, dir, cylinder.pos));
// 	if (l > vect_norm(vec_rest(cylinder.top, cylinder.pos)))
// 		return (ft_cap(mrt, cylinder, dir, cylinder.top));
// 	return (-1);
// }