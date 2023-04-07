/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:18 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 18:30:23 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	contour_cone(t_mrt *mrt, t_vec *new, double c, double tang)
{
	t_discr	discr;
	double	radius;

	radius = mrt->cone[mrt->curr_obj.index].height * tang;
	discr = get_cone_disc(new, tang);
	if ((v_abs(discr.dscr) < 0.0008 * c * radius && !cam_in_cone(mrt, \
	mrt->curr_obj.index, new[0], tang)) || v_abs((new[0].z + (c * new[1].z)) \
	- mrt->cone[mrt->curr_obj.index].height) < 0.05)
		return (1);
	return (0);
}

void	fov_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.chg_opt == FOV)
	{
		if (key == PLUS && mrt->cone[mrt->curr_obj.index].angle < PI)
			mrt->cone[mrt->curr_obj.index].angle += 0.05;
		if (key == MINUS && mrt->cone[mrt->curr_obj.index].angle > 0.1)
			mrt->cone[mrt->curr_obj.index].angle -= 0.05;
	}
}

t_base	cone_get_tang_base(t_mrt *mrt, t_inter inter, t_vec orig, t_vec cyl_c)
{
	t_base	ret;

	ret = mrt->cone[inter.index].base;
	if (inter.cuad_ctr == 2)
	{
		ret.n3 = orig;
		ret.n1 = fill_coord(cos(cyl_c.y + (PI / 2)), \
		sin(cyl_c.y + (PI / 2)), 0);
		ret.n2 = normalize(cross_prod(ret.n3, ret.n1));
	}
	return (ret);
}

t_vec	cone_bumped(t_mrt *mrt, t_inter inter, t_vec without)
{
	t_mtrx	chg;
	t_vec	new_inter[2];
	t_vec	new_normal;
	t_vec	ret;
	t_base	tang_base;

	ret = without;
	chg = fill_mtrx(mrt->cone[inter.index].base.n1,
			mrt->cone[inter.index].base.n2,
			mrt->cone[inter.index].base.n3);
	new_inter[0] = vec_rest(inter.inter_coor, mrt->cone[inter.index].pos);
	new_inter[0] = mtrx_by_vec(chg, new_inter[0]);
	new_inter[1] = get_cyl_coor(new_inter[0]);
	new_normal = cone_nml_frm_map(mrt, inter, new_inter[0], new_inter[1]);
	tang_base = cone_get_tang_base(mrt, inter, mtrx_by_vec(chg, without), \
	new_inter[1]);
	ret = get_bump_nrml(new_normal, tang_base, mtrx_trsp(chg));
	if (dot_prod(ret, without) < 0)
		ret = normalize(scal_vec(-1, ret));
	return (ret);
}
