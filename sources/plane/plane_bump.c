/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:59:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 01:02:02 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	pl_bmp_1(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.bump_map.height;
	width = mrt->plane[inter.index].option.bump_map.width;
	bump_coor[0] = (int)integer_part(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan) % (height - 1);
	bump_coor[1] = (int)integer_part(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan) % (width - 1);
	if (bump_coor[0] > height - 1)
		bump_coor[0] = height - 1;
	if (bump_coor[1] > width - 1)
		bump_coor[1] = width - 1;
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	pl_bmp_2(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.bump_map.height;
	width = mrt->plane[inter.index].option.bump_map.width;
	bump_coor[0] = height \
	- ((int)integer_part(v_abs(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan)) % (height - 1));
	bump_coor[1] = (int)integer_part(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan) % (width - 1);
	if (bump_coor[0] > height - 1)
		bump_coor[0] = height - 1;
	if (bump_coor[1] > width - 1)
		bump_coor[1] = width - 1;
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	pl_bmp_3(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.bump_map.height;
	width = mrt->plane[inter.index].option.bump_map.width;
	bump_coor[0] = (int)integer_part(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan) % (height - 1);
	bump_coor[1] = width - ((int)integer_part(v_abs(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan)) % (width - 1));
	if (bump_coor[0] > height - 1)
		bump_coor[0] = height - 1;
	if (bump_coor[1] > width - 1)
		bump_coor[1] = width - 1;
	ret = bump_nrml_by_coor(&mrt->plane[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_vec	pl_bmp_4(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		bump_coor[2];
	t_vec	ret;
	int		width;
	int		height;

	width = mrt->plane[inter.index].option.bump_map.width;
	height = mrt->plane[inter.index].option.bump_map.height;
	bump_coor[0] = height - ((int)integer_part(v_abs(new_inter.x / \
	mrt->plane[inter.index].option.bump_map.res_plan)) % (height - 1));
	bump_coor[1] = width - ((int)integer_part(v_abs(new_inter.y / \
	mrt->plane[inter.index].option.bump_map.res_plan)) % (width - 1));
	if (bump_coor[0] > height - 1)
		bump_coor[0] = height - 1;
	if (bump_coor[1] > width - 1)
		bump_coor[1] = width - 1;
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
