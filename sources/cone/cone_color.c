/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:27:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 18:42:19 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
