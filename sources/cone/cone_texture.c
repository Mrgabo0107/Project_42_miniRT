/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:27:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 18:42:11 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_cone_ang_resol(t_mrt *mrt, t_inter inter, double r_c, \
t_vec cyl_c)
{
	double	arc;
	int		i_res_c;
	int		n_img;
	double	ret;

	ret = r_c;
	arc = r_c / (cyl_c.y * tan(mrt->cone[inter.index].angle / 2));
	i_res_c = (int)((2 * PI) / arc);
	n_img = i_res_c / (mrt->cone[inter.index].option.texture.width - 1);
	if (n_img <= 0)
		ret = (2 * PI) / (mrt->cone[inter.index].option.texture.width - 1);
	else
	{
		if (decimal_part((2 * PI) / n_img) <= 0.5)
			ret = (2 * PI) / (n_img * i_res_c);
		else
			ret = (2 * PI) / ((n_img + 1) * i_res_c);
	}
	return (ret);
}

static double	get_cone_bdy_res(t_mrt *mrt, t_inter inter, double r_c)
{
	int		i_res_h;
	int		n_img;
	double	ret;

	ret = r_c;
	i_res_h = (int)integer_part(mrt->cone[inter.index].height / r_c);
	n_img = i_res_h / (mrt->cone[inter.index].option.texture.height - 1);
	if (n_img <= 0)
		ret = mrt->cone[inter.index].height / \
		(mrt->cone[inter.index].option.texture.height - 1);
	else
	{
		if (decimal_part(mrt->cone[inter.index].height / n_img) <= 0.5)
			ret = mrt->cone[inter.index].height / (n_img * i_res_h);
		else
			ret = mrt->cone[inter.index].height / ((n_img + 1) * i_res_h);
	}
	return (ret);
}

t_rgb	cone_cap_txt_fr_map(t_mrt *mrt, t_inter inter, t_vec c_cr, \
t_c_bump_val values)
{
	int		bump_coor[2];
	t_rgb	color;

	color = inter.color;
	if (values.i_diam > 6)
	{
		bump_coor[0] = (mrt->cone[inter.index].option.texture.height / 2) \
		+ (int)integer_part(c_cr.x / values.res_cap);
		bump_coor[1] = (mrt->cone[inter.index].option.texture.width / 2) \
		+ ((int)integer_part(c_cr.y / values.res_cap));
		pthread_mutex_lock(mrt->mutexs);
		pthread_mutex_unlock(mrt->mutexs);
	}
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->cone[inter.index].option.texture.array \
	[bump_coor[0]][bump_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	cone_body_txt_fr_map(t_mrt *mrt, t_inter inter, t_vec cyl_c, \
t_c_bump_val values)
{
	int		bump_coor[2];
	double	res_circ;
	double	res_h;
	t_rgb	color;

	color = inter.color;
	res_circ = get_cone_ang_resol(mrt, inter, values.res_cap, cyl_c);
	res_h = get_cone_bdy_res(mrt, inter, values.res_cap);
	bump_coor[1] = (int)integer_part(cyl_c.y / res_circ) % \
	mrt->cone[inter.index].option.texture.width - 1;
	bump_coor[0] = (mrt->cone[inter.index].option.texture.height - 1) \
	- (int)integer_part((cyl_c.z + ((mrt->cone[inter.index].height) / 2)) \
	/ res_h) % (mrt->cone[inter.index].option.texture.height - 1);
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->cone[inter.index].option.texture.array \
	[bump_coor[0]][bump_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	get_cone_texture(t_mrt *mrt, t_inter inter)
{
	t_mtrx			chg;
	t_vec			new_inter[2];
	t_c_bump_val	values;
	t_rgb			color;

	if (!mrt->cone[inter.index].option.texture_ctrl)
		return (inter.color);
	color = inter.color;
	chg = fill_mtrx(mrt->cone[inter.index].base.n1,
			mrt->cone[inter.index].base.n2,
			mrt->cone[inter.index].base.n3);
	new_inter[0] = vec_rest(inter.inter_coor, mrt->cone[inter.index].pos);
	new_inter[0] = mtrx_by_vec(chg, new_inter[0]);
	new_inter[1] = get_cyl_coor(new_inter[0]);
	values.i_diam = i_min_v(mrt->cone[inter.index].option.texture.height,
			mrt->cone[inter.index].option.texture.width);
	values.res_cap = (2 * mrt->cone[inter.index].height * \
	tan(mrt->cone[inter.index].angle / 2)) / (values.i_diam);
	if (inter.cuad_ctr == 1)
		color = cone_cap_txt_fr_map(mrt, inter, new_inter[0], values);
	if (inter.cuad_ctr == 2)
		color = cone_body_txt_fr_map(mrt, inter, new_inter[1], values);
	return (color);
}
