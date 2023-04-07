/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:27:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 18:29:53 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_cone_ang_resol(t_mrt *mrt, t_inter inter, \
double r_c, t_vec cyl_c)
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

t_c_chess	get_cone_bdy_col(t_mrt *mrt, int i, t_vec coor, t_rgb color)
{
	double		aux_dist;
	t_c_chess	ret;

	ret.color = color;
	ret.even_ctrl = 0;
	aux_dist = integer_part((mrt->cone[i].height
				* int_pow(2, mrt->cone[i].option.chess_ctrl))
			/ (PI * mrt->cone[i].height * tan(mrt->cone[i].angle / 2)));
	if ((int)aux_dist % 2 == 1)
		aux_dist += 1.0;
	aux_dist = mrt->cone[i].height / aux_dist;
	if (((int)v_abs(integer_part(int_pow(2, mrt->cone[i].option.chess_ctrl) \
		* (coor.y / PI))) % 2 == 1 && (int)integer_part(v_abs(coor.z \
		- mrt->cone[i].height) / aux_dist) % 2 == 1) \
		|| (((int)v_abs(integer_part(int_pow(2, \
		mrt->cone[i].option.chess_ctrl) * (coor.y / PI))) % 2 \
		== 0 && (int)integer_part(v_abs(coor.z - mrt->cone[i].height) / \
		aux_dist) % 2 == 0)))
	{
		ret.color = mrt->cone[i].option.check_color;
		ret.even_ctrl = (int)integer_part(mrt->cone[i].height \
		/ aux_dist) % 2;
	}
	return (ret);
}

t_rgb	get_cone_color(t_mrt *mrt, int i, t_vec *new, t_cuad_ctr ctr)
{
	t_vec		new_inter;
	t_rgb		ret;
	t_c_chess	ctrl;

	ret = mrt->cone[i].color;
	if (mrt->cone[i].option.chess_ctrl > 0)
	{
		new_inter = get_cyl_coor(vec_sum(new[0], scal_vec(ctr.c, new[1])));
		ctrl = get_cone_bdy_col(mrt, i, new_inter, ret);
		if (ctr.cap_ctrl == 2)
			ret = ctrl.color;
		if ((ctr.cap_ctrl == 1)
			&& ((int)v_abs(integer_part(
						int_pow(2, mrt->cone[i].option.chess_ctrl)
						* (new_inter.y / PI)))) % 2
			== (ctrl.even_ctrl + ctr.cap_ctrl) % 2)
			ret = mrt->cone[i].option.check_color;
	}
	return (ret);
}
