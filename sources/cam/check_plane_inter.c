/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_inter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:07:15 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/28 17:22:59 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	distance_to_plane(t_vec start_point, t_vec plane_pos,
		t_vec plane_dir, t_vec ray)
{
	t_vec	plane_to_point;
	double	den;

	den = dot_prod(plane_dir, ray);
	if (v_abs(den) > 0.001)
	{
		plane_to_point = vec_rest(plane_pos, start_point);
		return (dot_prod(plane_dir, plane_to_point) / den);
	}
	return (-1);
}

void	check_planes(t_mrt *mrt, t_inter *ctrl, t_vec dir)
{
	int		i;
	double	c;
	t_vec	norm;
	t_vec	inter_coor;

	i = 0;
	while (i < mrt->obj_count[PLANE])
	{
		c = distance_to_plane(mrt->cam.pos, mrt->plane[i].pos,
				mrt->plane[i].dir, dir);
		if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			inter_coor = vec_sum(mrt->cam.pos, scal_vec(c, dir));
			// if (dot_prod(mrt->plane[i].dir, 
			// vec_rest(mrt->cam.pos, inter_coor)) < 0)
			// 	norm = scal_vec(-1, mrt->plane[i].dir);
			// else
			norm = mrt->plane[i].dir;
			*ctrl = (t_inter){ctrl->pxl, PLANE, i, c, \
			inter_coor, norm};
		}
		i++;
	}
}
