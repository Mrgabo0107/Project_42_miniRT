/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:23:54 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/30 01:23:28 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	pln_col_case1(t_mrt *mrt, int index, t_vec new_inter, t_rgb color)
{
	if ((((int)v_abs(integer_part(new_inter.x \
	* mrt->plane[index].option.chess_ctrl)) % 2 == 1 \
	&& (int)v_abs(integer_part(new_inter.y \
	* mrt->plane[index].option.chess_ctrl)) % 2 == 1)) \
	|| ((int)v_abs(integer_part(new_inter.x \
	* mrt->plane[index].option.chess_ctrl)) % 2 == 0 \
	&& (int)v_abs(integer_part(new_inter.y \
	* mrt->plane[index].option.chess_ctrl)) % 2 == 0))
		return (mrt->plane[index].option.check_color);
	return (color);
}

t_rgb	pln_col_case2(t_mrt *mrt, int index, t_vec new_inter, t_rgb color)
{
	int	c;

	c = 2;
	if (mrt->plane[index].option.chess_ctrl % 2 == 0)
		c = 1;
	if (((int)v_abs(integer_part((new_inter.x - 1) \
	* mrt->plane[index].option.chess_ctrl) + c) % 2 == 1 \
	&& (int)integer_part(new_inter.y \
	* mrt->plane[index].option.chess_ctrl) % 2 == 1) \
	|| ((int)v_abs(integer_part((new_inter.x - 1) \
	* mrt->plane[index].option.chess_ctrl) + c) % 2 == 0 \
	&& (int)integer_part(new_inter.y \
	* mrt->plane[index].option.chess_ctrl) % 2 == 0))
		return (mrt->plane[index].option.check_color);
	return (color);
}

t_rgb	pln_col_case3(t_mrt *mrt, int index, t_vec new_inter, t_rgb color)
{
	int	c;

	c = 2;
	if (mrt->plane[index].option.chess_ctrl % 2 == 0)
		c = 1;
	if (((int)v_abs(integer_part(new_inter.x \
	* mrt->plane[index].option.chess_ctrl)) % 2 == 1 \
	&& (int)v_abs(integer_part((new_inter.y - 1) \
	* mrt->plane[index].option.chess_ctrl) + c) % 2 == 1) \
	|| ((int)v_abs(integer_part(new_inter.x \
	* mrt->plane[index].option.chess_ctrl)) % 2 == 0 \
	&& (int)v_abs(integer_part((new_inter.y - 1) \
	* mrt->plane[index].option.chess_ctrl) + c) % 2 == 0))
		return (mrt->plane[index].option.check_color);
	return (color);
}

t_rgb	get_plane_color(t_mrt *mrt, int index, t_vec intrsc)
{
	t_mtrx	chg;
	t_vec	new_inter;
	t_rgb	ret;

	ret = mrt->plane[index].color;
	if (mrt->plane[index].option.chess_ctrl > 0)
	{
		chg = fill_mtrx(mrt->plane[index].base.n1, mrt->plane[index].base.n2,
				mrt->plane[index].base.n3);
		new_inter = vec_rest(intrsc, mrt->plane[index].pos);
		new_inter = mtrx_by_vec(chg, new_inter);
		if (new_inter.x >= 0 && new_inter.y >= 0)
			ret = pln_col_case1(mrt, index, new_inter, ret);
		if (new_inter.x < 0 && new_inter.y >= 0)
			ret = pln_col_case2(mrt, index, new_inter, ret);
		if (new_inter.x < 0 && new_inter.y < 0)
			ret = pln_col_case1(mrt, index, new_inter, ret);
		if (new_inter.x >= 0 && new_inter.y < 0)
			ret = pln_col_case3(mrt, index, new_inter, ret);
	}
	return (ret);
}
