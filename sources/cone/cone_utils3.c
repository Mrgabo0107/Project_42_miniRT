/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:27:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 14:20:00 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	cone_cap_nrml_fr_map(t_mrt *mrt, t_inter inter, t_vec c_cr, \
t_c_bump_val values)
{
	int		bump_coor[2];
	t_vec	ret;

	ret = fill_coord(0, 0, 1);
	if (values.i_diam > 6)
	{
		bump_coor[0] = (mrt->cone[inter.index].option.bump_map.height / 2) \
		+ (int)integer_part(c_cr.x / values.res_cap);
		bump_coor[1] = (mrt->cone[inter.index].option.bump_map.width / 2) \
		+ ((int)integer_part(c_cr.y / values.res_cap));
		pthread_mutex_lock(mrt->mutexs);
		ret = bump_nrml_by_coor(&mrt->cone[inter.index].option, \
		bump_coor[0], bump_coor[1], 0.4);
		pthread_mutex_unlock(mrt->mutexs);
	}
	return (ret);
}

double	get_cone_ang_resol(t_mrt *mrt, t_inter inter, double r_c, t_vec cyl_c)
{
	double	arc;
	int		i_res_c;
	int		n_img;
	double	ret;

	ret = r_c;
	arc = r_c / (cyl_c.y * tan(mrt->cone[inter.index].angle / 2));
	i_res_c = (int)((2 * PI) / arc);
	n_img = i_res_c / (mrt->cone[inter.index].option.bump_map.width - 1);
	if (n_img <= 0)
		ret = (2 * PI) / (mrt->cone[inter.index].option.bump_map.width - 1);
	else
	{
		if (decimal_part((2 * PI) / n_img) <= 0.5)
			ret = (2 * PI) / (n_img * i_res_c);
		else
			ret = (2 * PI) / ((n_img + 1) * i_res_c);
	}
	return (ret);
}

double	get_cone_bdy_res(t_mrt *mrt, t_inter inter, double r_c)
{
	int		i_res_h;
	int		n_img;
	double	ret;

	ret = r_c;
	i_res_h = (int)integer_part(mrt->cone[inter.index].height / r_c);
	n_img = i_res_h / (mrt->cone[inter.index].option.bump_map.height - 1);
	if (n_img <= 0)
		ret = mrt->cone[inter.index].height / \
		(mrt->cone[inter.index].option.bump_map.height - 1);
	else
	{
		if (decimal_part(mrt->cone[inter.index].height / n_img) <= 0.5)
			ret = mrt->cone[inter.index].height / (n_img * i_res_h);
		else
			ret = mrt->cone[inter.index].height / ((n_img + 1) * i_res_h);
	}
	return (ret);
}

t_vec	cone_body_nrml_fr_map(t_mrt *mrt, t_inter inter, t_vec cyl_c, \
t_c_bump_val values)
{
	int		bump_coor[2];
	double	res_circ;
	double	res_h;
	t_vec	ret;

	(void)mrt;
	(void)inter;
	(void)cyl_c;
	(void)values;

	ret = fill_coord(0, 0, 1);
	res_circ = get_cone_ang_resol(mrt, inter, values.res_cap, cyl_c);
	res_h = get_cone_bdy_res(mrt, inter, values.res_cap);
	bump_coor[1] = (int)integer_part(cyl_c.y / res_circ) % \
	mrt->cone[inter.index].option.bump_map.width - 1;
	bump_coor[0] = (mrt->cone[inter.index].option.bump_map.height - 1) \
	- (int)integer_part((cyl_c.z + ((mrt->cone[inter.index].height) / 2)) \
	/ res_h) % (mrt->cone[inter.index].option.bump_map.height - 1);
	pthread_mutex_lock(mrt->mutexs);
	ret = bump_nrml_by_coor(&mrt->cone[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	pthread_mutex_unlock(mrt->mutexs);
	return (ret);
}

t_vec	cone_nml_frm_map(t_mrt *mrt, t_inter inter, t_vec c_cr, t_vec cyl_cr)
{
	t_vec			ret;
	t_c_bump_val	values;

	values.i_diam = i_min_v(mrt->cone[inter.index].option.bump_map.height,
			mrt->cone[inter.index].option.bump_map.width);
	values.res_cap = (2 * mrt->cone[inter.index].height * \
	tan(mrt->cone[inter.index].angle / 2)) / (values.i_diam);
	ret = fill_coord(0, 0, 1);
	if (inter.cuad_ctr == 1)
		ret = cone_cap_nrml_fr_map(mrt, inter, c_cr, values);
	if (inter.cuad_ctr == 2)
		ret = cone_body_nrml_fr_map(mrt, inter, cyl_cr, values);
	return (ret);
}
