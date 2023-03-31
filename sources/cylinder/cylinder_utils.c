/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:07:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/31 07:24:39 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_base	cyl_get_tang_base(t_mrt *mrt, t_inter inter, t_vec orig)
{
	t_base	ret;

	ret = mrt->cylinder[inter.index].base;
	if (inter.cyl_ctrl == 3)
	{
		ret.n3 = orig;
		ret.n2 = mrt->cylinder[inter.index].base.n3;
		ret.n1 = normalize(cross_prod(ret.n2, ret.n3));
	}
	return (ret);
}

t_vec	cyl_bumped(t_mrt *mrt, t_inter inter, t_vec without)
{
	t_mtrx	chg;
	t_vec	new_inter[2];
	t_vec	new_normal;
	t_vec	ret;
	t_base	tang_base;

	chg = fill_mtrx(mrt->cylinder[inter.index].base.n1,
			mrt->cylinder[inter.index].base.n2,
			mrt->cylinder[inter.index].base.n3);
	new_inter[0] = vec_rest(inter.inter_coor, mrt->cylinder[inter.index].pos);
	new_inter[0] = mtrx_by_vec(chg, new_inter[0]);
	new_inter[1] = get_cyl_coor(new_inter[0]);
	new_normal = cyl_normal_from_map(mrt, inter, new_inter[0], new_inter[1]);
	tang_base = cyl_get_tang_base(mrt, inter, mtrx_by_vec(chg, without));
	ret = get_bump_nrml(new_normal, tang_base, mtrx_trsp(chg));
	return (ret);
}

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
	// if (mrt->cylinder[inter.index].option.b_mp_ctrl == 1)
	// 	ret = cyl_bumped(mrt, inter, ret);
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
