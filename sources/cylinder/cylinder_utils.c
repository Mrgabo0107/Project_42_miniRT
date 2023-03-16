/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:07:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/15 22:47:12 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_cylinder(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = fill_coord(0, 0, 0);
	if (inter.cyl_ctrl == 1)
		ret = mrt->cylinder[inter.index].dir;
	else if (inter.cyl_ctrl == 2)
		ret = scal_vec(-1, mrt->cylinder[inter.index].dir);
	else if (inter.cyl_ctrl == 3)
		ret = vec_rest(inter.inter_coor,
				vec_sum(mrt->cylinder[inter.index].pos,
					scal_vec(dot_prod(vec_rest(inter.inter_coor,
								mrt->cylinder[inter.index].pos),
							mrt->cylinder[inter.index].dir),
						mrt->cylinder[inter.index].dir)));
	if (inter.is_in_obj)
		ret = scal_vec(-1, ret);
	return (ret);
}

int	cam_in_cyl(t_mrt *mrt, int indx, t_vec new_cam)
{
	if (int_pow(new_cam.x, 2) + int_pow(new_cam.y, 2)
		<= int_pow(mrt->cylinder[indx].radius, 2)
		&& v_abs(new_cam.z) <= mrt->cylinder[indx].height / 2)
		return (1);
	return (0);
}
