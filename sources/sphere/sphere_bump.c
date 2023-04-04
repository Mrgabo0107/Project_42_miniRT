/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:50:57 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/04 20:03:31 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	sph_normal_from_map(t_mrt *mrt, t_inter inter, t_vec sph_coor)
{
	int		bump_coor[2];
	t_vec	ret;
	double	pol_res;
	double	as_res;

	pol_res = PI / mrt->sphere[inter.index].option.bump_map.height;
	as_res = (2 * PI) / (mrt->sphere[inter.index].option.bump_map.width - 1);
	bump_coor[0] = (int)integer_part(sph_coor.y / pol_res);
	bump_coor[1] = (int)integer_part(sph_coor.z / as_res);
	ret = bump_nrml_by_coor(&mrt->sphere[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_base	sph_get_tang_base(t_vec	sph_coor, t_vec z)
{
	t_base	ret;

	ret.bs_orig = fill_coord(0, 0, 0);
	ret.n1 = fill_coord(sin(sph_coor.y), cos(sph_coor.y), 0);
	ret.n3 = z;
	ret.n2 = normalize(cross_prod(ret.n3, ret.n1));
	return (ret);
}

t_vec	sphere_bumped(t_mrt *mrt, t_inter inter, t_vec without)
{
	t_mtrx	chg;
	t_vec	new_inter;
	t_vec	new_normal;
	t_vec	ret;
	t_base	tang_base;

	chg = fill_mtrx(mrt->sphere[inter.index].base.n1,
			mrt->sphere[inter.index].base.n2,
			mrt->sphere[inter.index].base.n3);
	new_inter = vec_rest(inter.inter_coor, mrt->sphere[inter.index].center);
	new_inter = mtrx_by_vec(chg, new_inter);
	new_inter = get_spheric_coord(new_inter);
	new_normal = sph_normal_from_map(mrt, inter, new_inter);
	tang_base = sph_get_tang_base(new_inter, mtrx_by_vec(chg, without));
	ret = get_bump_nrml(new_normal, tang_base, mtrx_trsp(chg));
	if (dot_prod(ret, without) < 0)
		ret = normalize(scal_vec(-1, ret));
	return (ret);
}
