/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:59:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/30 03:50:45 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	pl_bmp_1(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;

	bump_coor[0] = (int)integer_part(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan) \
	% (mrt->plane[inter.index].option.bump_map.height - 1);
	bump_coor[1] = (int)integer_part(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan) % \
	(mrt->plane[inter.index].option.bump_map.width - 1);
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	pl_bmp_2(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;

	bump_coor[0] = mrt->plane[inter.index].option.bump_map.height \
	- ((int)integer_part(v_abs(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan - 1)) \
	% mrt->plane[inter.index].option.bump_map.height);
	bump_coor[1] = (int)integer_part(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan) % \
	(mrt->plane[inter.index].option.bump_map.width - 1);
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	pl_bmp_3(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;

	bump_coor[0] = (int)integer_part(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan) \
	% (mrt->plane[inter.index].option.bump_map.height - 1);
	bump_coor[1] = mrt->plane[inter.index].option.bump_map.width - \
	((int)integer_part(v_abs(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan - 1)) % \
	mrt->plane[inter.index].option.bump_map.width);
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	pl_bmp_4(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;

	bump_coor[0] = mrt->plane[inter.index].option.bump_map.height \
	- ((int)integer_part(v_abs(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan - 1)) \
	% mrt->plane[inter.index].option.bump_map.height);
	bump_coor[1] = mrt->plane[inter.index].option.bump_map.width - \
	((int)integer_part(v_abs(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan - 1)) % \
	mrt->plane[inter.index].option.bump_map.width);
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	plane_bumped(t_mrt *mrt, t_inter inter, t_vec without)
{
	t_mtrx	chg;
	t_vec	new_inter;
	t_vec	ret;

	ret = without;
	chg = fill_mtrx(mrt->plane[inter.index].base.n1,
			mrt->plane[inter.index].base.n2,
			mrt->plane[inter.index].base.n3);
	new_inter = vec_rest(inter.inter_coor, mrt->plane[inter.index].pos);
	new_inter = mtrx_by_vec(chg, new_inter);
	if (new_inter.x >= 0 && new_inter.y >= 0)
		ret = pl_bmp_1(mrt, inter, new_inter);
	if (new_inter.x < 0 && new_inter.y >= 0)
		ret = pl_bmp_2(mrt, inter, new_inter);
	if (new_inter.x >= 0 && new_inter.y < 0)
		ret = pl_bmp_3(mrt, inter, new_inter);
	if (new_inter.x < 0 && new_inter.y < 0)
		ret = pl_bmp_4(mrt, inter, new_inter);
	return (ret);
}
