/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 00:34:41 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 01:55:57 gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_cone(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;
	t_vec	curr;

	ret = fill_coord(0, 0, 0);
	curr = fill_coord(0, 0, inter.inter_coor.z \
	* (1 + tan(mrt->cone[inter.index].angle / 2)));
	if (inter.cuad_ctr == 1)
		ret = mrt->cone[inter.index].dir;
	else if (inter.cuad_ctr == 2)
		ret = normalize(vec_rest(inter.inter_coor, curr));
	// printf("\nnorm %f, coor.x %f, %f, %f\n", vect_norm(ret), ret.x, ret.y, ret.z );
	return (ret);
}

int	cam_in_cone(t_mrt *mrt, int indx, t_vec *new, double tang)
{
	double	radius;

	radius = new[2].z * tang;
	if (int_pow(new[0].x, 2) + int_pow(new[1].y, 2)
		<= int_pow(radius, 2)
		&& v_abs(new[0].z) <= mrt->cone[indx].height)
		return (1);
	return (0);
}
