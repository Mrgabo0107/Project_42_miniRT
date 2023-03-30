/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:50:57 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/30 04:30:56 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	normal_from_map(t_mrt *mrt, t_inter inter, t_vec sph_coor)
{
	int		bump_coor[2];
	t_vec	ret;

	bump_coor[0] = (int)integer_part((sph_coor.y * \
	mrt->sphere[inter.index].option.bump_map.width) / (2 * PI));
	bump_coor[1] = (int)integer_part(((sph_coor.z + (PI / 2)) * \
	mrt->sphere[inter.index].option.bump_map.height) / PI);
	ret = bump_nrml_by_coor(&mrt->sphere[inter.index].option, \
	bump_coor[0], bump_coor[1], 0.4);
	return (ret);
}

t_base	get_tang_base(t_vec	sph_coor, t_vec z)
{
	t_base	ret;

	ret.bs_orig = fill_coord(0, 0, 0);
	ret.n1 = fill_coord(asin(sph_coor.y + PI), acos(sph_coor.y + PI), 0);
	ret.n3 = z;
	ret.n2 = normalize(cross_prod(ret.n3, ret.n1));
	return (ret);
}

t_vec	get_sph_bump_nrml(t_vec new_n, t_base tang_base, t_mtrx chg)
{
	t_vec	ret;

	ret = vec_sum(vec_sum(scal_vec(new_n.x, tang_base.n1), \
	scal_vec(new_n.y, tang_base.n2)), scal_vec(new_n.z, tang_base.n3));
	ret = mtrx_by_vec(chg, ret);
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
	new_normal = normal_from_map(mrt, inter, new_inter);
	tang_base = get_tang_base(new_inter, mtrx_by_vec(chg, without));
	ret = get_sph_bump_nrml(new_normal, tang_base, mtrx_trsp(chg));
	return (ret);
}