/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_inter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/24 22:28:00 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
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
// 	proj_len = vec_len(proj);
// 	c = dot_prod(cylinder.dir, proj_to_cam) / dot_prod(cylinder.dir, dir);
// 	// if (proj_len > cylinder.radius)
// 	// 	return (-1);
// 	return (c);
// }

double	distance_to_cylinder(t_mrt *mrt, t_cylinder cylinder, t_vec dir)
{
	t_vec	h;
	t_vec	w;
	t_discr	discr;
	double	c;
	double	l;

	h = normalize(vec_sub(cylinder.top, cylinder.pos));
	w = vec_sub(mrt->cam.pos, cylinder.pos);
	discr.a = dot_prod(dir, dir) - pow(dot_prod(dir, h), 2);
	discr.b = 2 * (dot_prod(dir, w) - dot_prod(dir, h) * dot_prod(w, h));
	discr.c = dot_prod(w, w) - pow(dot_prod(w, h), 2) - pow(cylinder.radius, 2);
	discr.dscr = pow(discr.b, 2) - 4 * discr.a * discr.c;
	if (discr.dscr <= 0)
		return (-1);
	// else if (discr.dscr == 0)
		// c = -discr.b / (2 * discr.a);
	c = min_v(((-discr.b - sqrt(discr.dscr)) / (2 * discr.a)), \
	((-discr.b + sqrt(discr.dscr)) / (2 * discr.a)));
	l = dot_prod(vec_sum(mrt->cam.pos, scal_vec(c, dir)), h);
	if (l < 0 || l > vec_len(vec_sub(cylinder.top, cylinder.pos)))
		return (-1);
	return (c);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec dir)
{
	int		i;
	double	c;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		mrt->cylinder[i].top = vec_sum(mrt->cylinder[i].pos, \
		scal_vec(mrt->cylinder[i].height, mrt->cylinder[i].dir));
		c = distance_to_cylinder(mrt, mrt->cylinder[i], dir);
		// if (c > 0)
			// printf("cylinder index: %f\n", c);
		if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			ctrl->type = CYLINDER;
			ctrl->index = i;
			ctrl->dist = c;
			ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vec(c, dir));
		}
		i++;
	}
}
