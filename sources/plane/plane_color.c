/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:45:24 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/22 20:08:04 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_plane_color(t_mrt *mrt, int index, t_vec intrsc)
{
	t_mtrx	chg;
	t_vec	new_inter;

	if (mrt->plane[index].chess_ctrl > 0)
	{
		chg = fill_mtrx(mrt->plane[index].base.n1, mrt->plane[index].base.n2,
				mrt->plane[index].base.n3);
		new_inter = vec_rest(intrsc, mrt->plane[index].pos);
		new_inter = mtrx_by_vec(chg, new_inter);
		if (integer_part(new_inter.x) * integer_part(new_inter.y) > 0
			&& integer_part(new_inter.x) % 2 == 1
			&& integer_part(new_inter.y) % 2 == 1)
			return (mrt->plane[mrt->curr_obj.index].color1);
		else if (integer_part(new_inter.x) * integer_part(new_inter.y) <= 0
			&& integer_part(new_inter.x) % 2 == 0
			&& integer_part(new_inter.y) % 2 == 0)
			return (mrt->plane[mrt->curr_obj.index].color1);
	}
	return (mrt->plane[mrt->curr_obj.index].color);
}
