/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_inter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:07:15 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/27 16:57:55 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	distance_to_plane(t_vec point, t_vec pos, t_vec dir, t_vec ray)
{
	double	c;
	t_vec	plane_to_point;
	double	den;

	den = dot_prod(dir, ray);
	if (den == 0.0)
		return (-1);
	plane_to_point = vec_rest(pos, point);
	c = v_abs(dot_prod(dir, plane_to_point)) / den;
	return (c);
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
			if (dot_prod(mrt->plane[i].dir, vec_rest(mrt->cam.pos, inter_coor)) < 0)
			{
				norm = scal_vec(-1, mrt->plane[i].dir);
			}
			else
			{
				norm = mrt->plane[i].dir;
			}
			*ctrl = (t_inter){ctrl->pxl, PLANE, i, c, \
			inter_coor, norm};
		}
		i++;
	}
}
