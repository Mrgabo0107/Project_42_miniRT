/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:17:11 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/01 20:31:01 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	check_intersections(t_mrt *mrt, t_vec point, t_vec dir)
{
	t_inter	ret;

	ret.type = UNDEFINED;
	ret.index = 0;
	ret.dist = -1;
	check_planes(mrt, &ret, point, dir);
	check_spheres(mrt, &ret, point, dir);
	check_cylinders(mrt, &ret, point, dir);
	check_triangles(mrt, &ret, point, dir);
	return (ret);
}

t_inter	check_shaddow(t_mrt *mrt, t_inter *ctr, t_vec dir, double len)
{
	t_inter	ret;
	t_vec	point;

	point = vec_sum(ctr->inter_coor, scal_vec(0.0000001, ctr->norm));
	ret.type = UNDEFINED;
	ret.index = 0;
	ret.dist = -1;
	check_planes(mrt, &ret, point, dir);
	if (ret.dist != -1 && ret.dist < len)
		return (ret);
	check_spheres(mrt, &ret, point, dir);
	if (ret.dist != -1 && ret.dist < len)
		return (ret);
	check_cylinders(mrt, &ret, point, dir);
	if (ret.dist != -1 && ret.dist < len)
		return (ret);
	check_triangles(mrt, &ret, point, dir);
	return (ret);
}
