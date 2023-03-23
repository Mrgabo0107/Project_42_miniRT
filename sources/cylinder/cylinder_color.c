/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 03:01:45 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/23 04:45:52 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_body_color(t_mrt *mrt, int i, t_vec coor, t_rgb color)
{
	double	aux_dist;
	t_rgb	ret;

	ret = color;
	aux_dist = integer_part((mrt->cylinder[i].height
				* int_pow(2, mrt->cylinder[i].chess_ctrl))
			/ (PI * mrt->cylinder[i].radius));
	aux_dist = mrt->cylinder[i].height / aux_dist;
	if ((int)v_abs(integer_part(int_pow(2, mrt->cylinder[i].chess_ctrl)
				* (coor.y / PI))) % 2 == 1 && (int)integer_part(v_abs(coor.z
				- mrt->cylinder[i].height) / aux_dist) % 2 == 1
		|| (int)v_abs(integer_part(int_pow(2, mrt->cylinder[i].chess_ctrl)
				* (coor.y / PI))) % 2 == 0 && (int)integer_part(v_abs(coor.z
				- mrt->cylinder[i].height) / aux_dist) % 2 == 0)
		ret = mrt->cylinder[i].color1;
	return (ret);
}

t_rgb	get_cyl_color(t_mrt *mrt, int index, t_vec intrsc, t_cyl_ctrl ctr)
{
	t_mtrx	chg;
	t_vec	new_inter;
	t_rgb	ret;

	ret = mrt->cylinder[index].color;
	if (mrt->cylinder[index].chess_ctrl > 0)
	{
		chg = fill_mtrx(mrt->cylinder[index].base.n1,
				mrt->cylinder[index].base.n2,
				mrt->cylinder[index].base.n3);
		new_inter = vec_rest(intrsc, mrt->cylinder[index].pos);
		new_inter = mtrx_by_vec(chg, new_inter);
		new_inter = get_cyl_coor(new_inter);
		if ((ctr.cap_ctrl == 1 || ctr.cap_ctrl == 2)
			&& ((int)v_abs(integer_part(
						int_pow(2, mrt->cylinder[index].chess_ctrl)
						* (new_inter.y / PI)))) % 2 == 1)
			ret = mrt->cylinder[index].color1;
		if (ctr.cap_ctrl == 3)
			ret = get_body_color(mrt, index, new_inter, ret);
	}
	return (ret);
}
