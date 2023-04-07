/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 06:50:08 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 16:06:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_c_chess	get_body_color(t_mrt *mrt, int i, t_vec coor, t_rgb color)
{
	double		aux_dist;
	t_c_chess	ret;

	ret.color = color;
	ret.even_ctrl = 0;
	aux_dist = integer_part((mrt->cylinder[i].height
				* int_pow(2, mrt->cylinder[i].option.chess_ctrl))
			/ (PI * mrt->cylinder[i].radius));
	if ((int)aux_dist % 2 == 1)
		aux_dist += 1.0;
	aux_dist = mrt->cylinder[i].height / aux_dist;
	if (((int)v_abs(integer_part(int_pow(2, mrt->cylinder[i].option.chess_ctrl) \
		* (coor.y / PI))) % 2 == 1 && (int)integer_part(v_abs(coor.z \
		- mrt->cylinder[i].height) / aux_dist) % 2 == 1) \
		|| (((int)v_abs(integer_part(int_pow(2, \
		mrt->cylinder[i].option.chess_ctrl) * (coor.y / PI))) % 2 \
		== 0 && (int)integer_part(v_abs(coor.z - mrt->cylinder[i].height) / \
		aux_dist) % 2 == 0)))
	{
		ret.color = mrt->cylinder[i].option.check_color;
		ret.even_ctrl = (int)integer_part(mrt->cylinder[i].height \
		/ aux_dist) % 2;
	}
	return (ret);
}

t_rgb	get_cyl_color(t_mrt *mrt, int index, t_vec intrsc, t_cuad_ctr ctr)
{
	t_mtrx		chg;
	t_vec		new_inter;
	t_rgb		ret;
	t_c_chess	ctrl;

	ret = mrt->cylinder[index].color;
	if (mrt->cylinder[index].option.chess_ctrl > 0)
	{
		chg = fill_mtrx(mrt->cylinder[index].base.n1,
				mrt->cylinder[index].base.n2,
				mrt->cylinder[index].base.n3);
		new_inter = vec_rest(intrsc, mrt->cylinder[index].pos);
		new_inter = mtrx_by_vec(chg, new_inter);
		new_inter = get_cyl_coor(new_inter);
		ctrl = get_body_color(mrt, index, new_inter, ret);
		if (ctr.cap_ctrl == 3)
			ret = ctrl.color;
		if ((ctr.cap_ctrl == 1 || ctr.cap_ctrl == 2) && \
		((int)v_abs(integer_part(int_pow(2, \
		mrt->cylinder[index].option.chess_ctrl) * (new_inter.y / PI)))) % 2 \
		== (ctrl.even_ctrl + ctr.cap_ctrl) % 2)
			ret = mrt->cylinder[index].option.check_color;
	}
	return (ret);
}

t_rgb	cyl_cap_color_fr_map(t_mrt *mrt, t_inter inter, t_vec c_cr, \
t_c_bump_val values)
{
	int		bump_coor[2];
	t_rgb	color;

	if (values.i_diam > 6)
	{
		bump_coor[0] = (mrt->cylinder[inter.index].option.texture.height / 2) \
		+ (int)integer_part(c_cr.x / values.res_cap);
		bump_coor[1] = (mrt->cylinder[inter.index].option.texture.width / 2) \
		+ ((int)integer_part(c_cr.y / values.res_cap));
	}
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->cylinder[inter.index].option.texture.array \
	[bump_coor[0]][bump_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	cyl_body_color_fr_map(t_mrt *mrt, t_inter inter, t_vec cyl_c, \
t_c_bump_val values)
{
	int		bump_coor[2];
	double	res_circ;
	double	res_h;
	t_rgb	color;

	res_circ = get_angular_resol(mrt, inter, values.res_cap, \
	mrt->cylinder[inter.index].option.texture.width);
	res_h = get_body_resol(mrt, inter, values.res_cap, \
	mrt->cylinder[inter.index].option.texture.height);
	bump_coor[1] = (int)integer_part(cyl_c.y / res_circ) % \
	mrt->cylinder[inter.index].option.texture.width - 1;
	bump_coor[0] = (mrt->cylinder[inter.index].option.texture.height - 1) \
	- (int)integer_part((cyl_c.z + ((mrt->cylinder[inter.index].height) / 2)) \
	/ res_h) % (mrt->cylinder[inter.index].option.texture.height - 1);
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->cylinder[inter.index].option.texture.array \
	[bump_coor[0]][bump_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	get_cyl_texture(t_mrt *mrt, t_inter inter)
{
	t_mtrx			chg;
	t_vec			new_inter[2];
	t_rgb			color;
	t_c_bump_val	values;

	if (!mrt->cylinder[inter.index].option.texture_ctrl)
		return (inter.color);
	chg = fill_mtrx(mrt->cylinder[inter.index].base.n1,
			mrt->cylinder[inter.index].base.n2,
			mrt->cylinder[inter.index].base.n3);
	new_inter[0] = vec_rest(inter.inter_coor, mrt->cylinder[inter.index].pos);
	new_inter[0] = mtrx_by_vec(chg, new_inter[0]);
	new_inter[1] = get_cyl_coor(new_inter[0]);
	color = inter.color;
	values.i_diam = i_min_v(mrt->cylinder[inter.index].option.texture.height,
			mrt->cylinder[inter.index].option.texture.width);
	values.res_cap = (2 * mrt->cylinder[inter.index].radius) / (values.i_diam);
	if (inter.cuad_ctr == 1 || inter.cuad_ctr == 2)
		color = cyl_cap_color_fr_map(mrt, inter, new_inter[0], values);
	if (inter.cuad_ctr == 3)
		color = cyl_body_color_fr_map(mrt, inter, new_inter[1], values);
	return (color);
}
