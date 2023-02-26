/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_inter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:07:15 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/26 18:15:42 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	distance_to_plane(t_vec point, t_vec pos, t_vec dir, t_vec ray)
{
	double	c;
	t_vec	plane_to_point;

	plane_to_point = vec_rest(pos, point);
	c = dot_prod(dir, plane_to_point) / dot_prod(dir, ray);
	return (c);
}

void	check_planes(t_mrt *mrt, t_inter *ctrl, t_vec dir)
{
	int		i;
	double	c;

	i = 0;
	while (i < mrt->obj_count[PLANE])
	{
		// printf("plane index: %d\n", i);
		c = distance_to_plane(mrt->cam.pos, mrt->plane[i].pos,
				mrt->plane[i].dir, dir);
		if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			ctrl->type = PLANE;
			ctrl->index = i;
			ctrl->dist = c;
			ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vec(c, dir));
		}
		i++;
	}
}
