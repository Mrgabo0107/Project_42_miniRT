/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 06:50:08 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/28 22:17:33 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cyl_chess	get_body_color(t_mrt *mrt, int i, t_vec coor, t_rgb color)
{
	double		aux_dist;
	t_cyl_chess	ret;

	ret.color = color;
	aux_dist = integer_part((mrt->cylinder[i].height
				* int_pow(2, mrt->cylinder[i].option.chess_ctrl))
			/ (PI * mrt->cylinder[i].radius));
	if ((int)aux_dist % 2 == 1)
		aux_dist += 1.0;
	aux_dist = mrt->cylinder[i].height / aux_dist;
	if (((int)v_abs(integer_part(int_pow(2, mrt->cylinder[i].option.chess_ctrl)
				* (coor.y / PI))) % 2 == 1 && (int)integer_part(v_abs(coor.z
				- mrt->cylinder[i].height) / aux_dist) % 2 == 1)
		|| (((int)v_abs(integer_part(int_pow(2, mrt->cylinder[i].option.chess_ctrl)
				* (coor.y / PI))) % 2 == 0 && (int)integer_part(v_abs(coor.z
				- mrt->cylinder[i].height) / aux_dist) % 2 == 0)))
	{
		ret.color = mrt->cylinder[i].option.check_color;
		ret.even_ctrl = (int)integer_part(mrt->cylinder[i].height / aux_dist)
		/ 2;
	}
	return (ret);
}

t_rgb	get_cyl_color(t_mrt *mrt, int index, t_vec intrsc, t_cyl_ctrl ctr)
{
	t_mtrx		chg;
	t_vec		new_inter;
	t_rgb		ret;
	t_cyl_chess	ctrl;

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
		if ((ctr.cap_ctrl == 1 || ctr.cap_ctrl == 2)
			&& ((int)v_abs(integer_part(
						int_pow(2, mrt->cylinder[index].option.chess_ctrl)
						* (new_inter.y / PI)))) % 2
			== (ctrl.even_ctrl + ctr.cap_ctrl) % 2)
			ret = mrt->cylinder[index].option.check_color;
	}
	return (ret);
}
