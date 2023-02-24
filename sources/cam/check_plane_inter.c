/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_inter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:07:15 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/24 21:14:28 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	distance_to_plane(t_mrt *mrt, t_plane plane, t_vec dir)
{
	double	c;
	t_vec	plane_to_cam;

	plane_to_cam = vec_rest(plane.pos, mrt->cam.pos);
	c = dot_prod(plane.dir, plane_to_cam) / dot_prod(plane.dir, dir);
	return (c);
}

// t_vec	plane_inter_coord(t_mrt *mrt, t_plane plane, t_vec dir)
// {
// 	t_vec	inter_coor;
// 	double	n1;
// 	double	n2;
// 	double	n3;
// 	double	t;

// 	n1 = plane.dir.x;
// 	n2 = plane.dir.y;
// 	n3 = plane.dir.z;
// 	t = (n1 * (plane.pos.x - mrt->cam.pos.x) + n2 * 
// 	(plane.pos.y - mrt->cam.pos.y) + n3 * (plane.pos.z - mrt->cam.pos.z)) 
// 	/ (n1 * dir.x + n2 * dir.y + n3 * dir.z);
// 	inter_coor.x = mrt->cam.pos.x + dir.x * t;
// 	inter_coor.y = mrt->cam.pos.y + dir.y * t;
// 	inter_coor.z = mrt->cam.pos.z + dir.z * t;
// 	return (inter_coor);
// }

void	check_planes(t_mrt *mrt, t_inter *ctrl, t_vec dir)
{
	int		i;
	double	c;

	i = 0;
	while (i < mrt->obj_count[PLANE])
	{
		// printf("plane index: %d\n", i);
		c = distance_to_plane(mrt, mrt->plane[i], dir);
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
