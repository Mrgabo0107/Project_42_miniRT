/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 14:59:33 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_discr	get_cyl_disc(t_cylinder cyl, t_vec new_cam, t_vec new_dirc)
{
	t_discr	ret;

	ret.a = int_pow(new_dirc.x, 2) + int_pow(new_dirc.y, 2);
	ret.b = 2 * ((new_cam.x * new_dirc.x)
			+ (new_cam.y * new_dirc.y));
	ret.c = int_pow(new_cam.x, 2) + int_pow(new_cam.y, 2)
		- int_pow(cyl.radius, 2);
	ret.dscr = int_pow(ret.b, 2) - (4 * (ret.a * ret.c));
	return (ret);
}

int	is_in_cap(double curr, t_cylinder cyl, t_vec new_cam, t_vec new_dirc)
{
	if (int_pow(new_cam.x + (curr * new_dirc.x), 2)
		+ int_pow(new_cam.y + (curr * new_dirc.y), 2)
		<= int_pow(cyl.radius, 2))
		return (1);
	return (0);
}

t_cuad_ctr	check_cyl_body(t_cuad_ctr *curr, t_cylinder cyl, t_vec nc, t_vec nd)
{
	t_cuad_ctr	ret;
	t_discr		discr;
	double		curre;

	ret = *curr;
	discr = get_cyl_disc(cyl, nc, nd);
	if (discr.dscr >= 0.0)
	{
		curre = solve_quad(&discr);
		if (curre > 0 && (ret.c == -1 || curre < ret.c)
			&& v_abs(vec_sum(nc, scal_vec(curre, nd)).z) <= cyl.height / 2)
		{
			ret.c = curre;
			ret.cap_ctrl = 3;
		}
	}
	return (ret);
}

t_cuad_ctr	get_dist_to_cyl(t_cylinder cyl, t_vec new_cam, t_vec new_dirc)
{
	double		curr;
	t_cuad_ctr	ret;

	ret.c = -1;
	ret.cap_ctrl = 0;
	if (v_abs(new_dirc.z) > 0.0001)
	{
		curr = ((cyl.height / (2 * new_dirc.z)) - (new_cam.z / new_dirc.z));
		if (curr > 0 && is_in_cap(curr, cyl, new_cam, new_dirc)
			&& (ret.c == -1 || curr < ret.c))
		{
			ret.c = curr;
			ret.cap_ctrl = 1;
		}
		curr = (-(cyl.height / (2 * new_dirc.z)) - (new_cam.z / new_dirc.z));
		if (curr > 0 && is_in_cap(curr, cyl, new_cam, new_dirc)
			&& (ret.c == -1 || curr < ret.c))
		{
			ret.c = curr;
			ret.cap_ctrl = 2;
		}
	}
	ret = check_cyl_body(&ret, cyl, new_cam, new_dirc);
	return (ret);
}

t_rgb	cyl_cap_color_fr_map(t_mrt *mrt, t_inter inter, t_vec c_cr, \
t_c_bump_val values)
{
	int		bump_coor[2];
	t_rgb	color;

	if (values.i_diam > 6)
	{
		bump_coor[0] = (mrt->cylinder[inter.index].option.bump_map.height / 2) \
		+ (int)integer_part(c_cr.x / values.res_cap);
		bump_coor[1] = (mrt->cylinder[inter.index].option.bump_map.width / 2) \
		+ ((int)integer_part(c_cr.y / values.res_cap));
	}
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->cylinder[inter.index].option.bump_map.array \
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

	res_circ = get_angular_resol(mrt, inter, values.res_cap);
	res_h = get_body_resol(mrt, inter, values.res_cap);
	bump_coor[1] = (int)integer_part(cyl_c.y / res_circ) % \
	mrt->cylinder[inter.index].option.bump_map.width - 1;
	bump_coor[0] = (mrt->cylinder[inter.index].option.bump_map.height - 1) \
	- (int)integer_part((cyl_c.z + ((mrt->cylinder[inter.index].height) / 2)) \
	/ res_h) % (mrt->cylinder[inter.index].option.bump_map.height - 1);
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->cylinder[inter.index].option.bump_map.array \
	[bump_coor[0]][bump_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	cyl_texture_from_map(t_mrt *mrt, t_inter inter,
		t_vec c_cr, t_vec cyl_cr)
{
	t_rgb			color;
	t_c_bump_val	values;

	color = inter.color;
	values.i_diam = i_min_v(mrt->cylinder[inter.index].option.bump_map.height,
			mrt->cylinder[inter.index].option.bump_map.width);
	values.res_cap = (2 * mrt->cylinder[inter.index].radius) / (values.i_diam);
	if (inter.cuad_ctr == 1 || inter.cuad_ctr == 2)
		color = cyl_cap_color_fr_map(mrt, inter, c_cr, values);
	if (inter.cuad_ctr == 3)
		color = cyl_body_color_fr_map(mrt, inter, cyl_cr, values);
	return (color);
}

t_rgb	get_cyl_texture(t_mrt *mrt, t_inter inter)
{
	t_mtrx	chg;
	t_vec	new_inter[2];
	t_rgb	color;

	chg = fill_mtrx(mrt->cylinder[inter.index].base.n1,
			mrt->cylinder[inter.index].base.n2,
			mrt->cylinder[inter.index].base.n3);
	new_inter[0] = vec_rest(inter.inter_coor, mrt->cylinder[inter.index].pos);
	new_inter[0] = mtrx_by_vec(chg, new_inter[0]);
	new_inter[1] = get_cyl_coor(new_inter[0]);
	color = cyl_texture_from_map(mrt, inter, new_inter[0], new_inter[1]);
	return (color);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int				i;
	t_cuad_ctr		ctr;
	t_vec			new_cam;
	t_vec			new_dirc;
	t_mtrx			chg_base;

	i = -1;
	while (++i < mrt->obj_count[CYLINDER])
	{
		new_cam = vec_rest(point, mrt->cylinder[i].pos);
		chg_base = fill_mtrx(mrt->cylinder[i].base.n1,
				mrt->cylinder[i].base.n2,
				mrt->cylinder[i].base.n3);
		new_cam = mtrx_by_vec(chg_base, new_cam);
		new_dirc = mtrx_by_vec(chg_base, dir);
		ctr = get_dist_to_cyl(mrt->cylinder[i], new_cam, new_dirc);
		if (ctr.c > 0 && (ctrl->dist == -1 || ctr.c < ctrl->dist))
		{
			*ctrl = (t_inter){CYLINDER, i, ctr.c, vec_sum(point, \
			scal_vec(ctr.c, dir)), fill_coord(0, 0, 0), \
			get_cyl_color(mrt, i, vec_sum(point, scal_vec(ctr.c, dir)), ctr), \
			mrt->cylinder[i].option, ctr.cap_ctrl, cam_in_cyl(mrt, i, new_cam)};
			ctrl->color = get_cyl_texture(mrt, *ctrl);
		}
	}
}
