/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:00:48 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/24 19:24:27 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_sphere_color(t_mrt *mrt, int index, t_vec intrsc)
{
	t_mtrx	chg;
	t_vec	new_inter;
	t_rgb	ret;
	// int		chess_ctrl;

	ret = mrt->sphere[index].color;
	if (mrt->sphere[index].option.chess_ctrl > 0)
	{
		chg = fill_mtrx(mrt->sphere[index].base.n1, mrt->sphere[index].base.n2,
				mrt->sphere[index].base.n3);
		new_inter = vec_rest(intrsc, mrt->sphere[index].center);
		new_inter = mtrx_by_vec(chg, new_inter);
		new_inter = get_spheric_coord(new_inter);
		if ((int)integer_part(int_pow(2, mrt->sphere[index].option.chess_ctrl) \
		* (new_inter.z / PI)) % 2 == 1 && (int)integer_part(int_pow(2, \
		mrt->sphere[index].option.chess_ctrl) * (new_inter.y / PI)) % 2 == 1)
			ret = mrt->sphere[index].option.check_color;
		if ((int)integer_part(int_pow(2, mrt->sphere[index].option.chess_ctrl) \
		* (new_inter.z / PI)) % 2 == 0 && (int)integer_part(int_pow(2, \
		mrt->sphere[index].option.chess_ctrl) * (new_inter.y / PI)) % 2 == 0)
			ret = mrt->sphere[index].option.check_color;
	}
	return (ret);
}
