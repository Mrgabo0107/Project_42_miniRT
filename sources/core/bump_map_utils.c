/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:49:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/04 05:15:19 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	col_to_b_w(t_rgb color, double h)
{
	return (h * ((0.299 * color.r) + (0.578 * color.g) + (0.114 * color.b)));
}

t_vec	bump_nrml_by_coor(t_option *opt, int x, int y, double h)
{
	t_vec	ret;
	t_rgb	curr_col;
	t_vec	result_vecs[2];

	ret = fill_coord(0, 0, 1);
	curr_col = convert_to_rgb(opt->bump_map.array[x][y]);
	if (x < opt->bump_map.height - 1 && y < opt->bump_map.width - 1)
	{
		result_vecs[0] = normalize(fill_coord(1, 0, \
		col_to_b_w(convert_to_rgb(opt->bump_map.array[x][y + 1]), h) \
		- col_to_b_w(curr_col, h)));
		result_vecs[1] = normalize(fill_coord(0, 1, \
		col_to_b_w(convert_to_rgb(opt->bump_map.array[x + 1][y]), h) \
		- col_to_b_w(curr_col, h)));
		ret = normalize(cross_prod(result_vecs[0], result_vecs[1]));
	}
	return (ret);
}

t_vec	get_bump_nrml(t_vec new_n, t_base tang_base, t_mtrx chg)
{
	t_vec	ret;

	ret = vec_sum(vec_sum(scal_vec(new_n.x, tang_base.n1), \
	scal_vec(new_n.y, tang_base.n2)), scal_vec(new_n.z, tang_base.n3));
	ret = mtrx_by_vec(chg, ret);
	return (ret);
}
