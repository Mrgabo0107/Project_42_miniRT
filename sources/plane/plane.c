/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:07:15 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/01 07:38:34 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_plane(t_mrt *mrt, t_inter inter)
{
	if (dot_prod(vec_rest(mrt->cam.pos, mrt->plane[inter.index].pos),
			mrt->plane[inter.index].dir) < 0.0)
		return (scal_vec(-1, mrt->plane[inter.index].dir));
	return (mrt->plane[inter.index].dir);
}

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

void	check_planes(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int		i;
	double	c;
	t_vec	inter_coor;

	i = 0;
	while (i < mrt->obj_count[PLANE])
	{
		if (v_abs(dot_prod(mrt->plane[i].dir, vec_rest(dir, point))) < 0.0001)
			i++;
		else
		{
			c = distance_to_plane(point, mrt->plane[i].pos,
					mrt->plane[i].dir, dir);
			if (c > 0 && (ctrl->dist == -1 || c < ctrl->dist))
			{
				inter_coor = vec_sum(point, scal_vec(c, dir));
				*ctrl = (t_inter){PLANE, i, c, inter_coor, \
				fill_coord(0, 0, 0)};
			}
			i++;
		}
	}
}
