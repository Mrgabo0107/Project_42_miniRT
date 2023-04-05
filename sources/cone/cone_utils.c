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

t_vec	normal_cyl_body(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;
	t_vec	new;
	t_vec	curr;
	t_mtrx	chg_base;

	chg_base = fill_mtrx(mrt->cone[inter.index].base.n1,
			mrt->cone[inter.index].base.n2,
			mrt->cone[inter.index].base.n3);
	new = vec_rest(inter.inter_coor, mrt->cone[inter.index].pos);
	new = mtrx_by_vec(chg_base, new);
	curr = fill_coord(0, 0, new.z * \
	(1 + int_pow(tan(mrt->cone[inter.index].angle / 2), 2)));
	ret = normalize(vec_rest(new, curr));
	ret = mtrx_by_vec(mtrx_trsp(chg_base), ret);
	return (ret);
}

t_vec	get_normal_cone(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = fill_coord(0, 0, 0);
	if (inter.cuad_ctr == 1)
		ret = mrt->cone[inter.index].dir;
	else if (inter.cuad_ctr == 2)
		ret = normal_cyl_body(mrt, inter);
	if (inter.is_in_obj)
		ret = scal_vec(-1, ret);
	return (ret);
}

double	solve_cone_quad(t_discr *info, t_vec *f_n)
{
	double	op1;
	double	op2;
	double	ret;

	if (info->dscr < 0.00001)
		return (-info->b / (2 * info->a));
	op1 = (-info->b + sqrt(info->dscr)) / (2 * info->a);
	op2 = (-info->b - sqrt(info->dscr)) / (2 * info->a);
	ret = min_v(op1, op2);
	if (ret < 0 || vec_sum(f_n[0], scal_vec(ret, f_n[1])).z < 0)
		return (max_v(op1, op2));
	return (ret);
}

int	cam_in_cone(t_mrt *mrt, int indx, t_vec n_c, double tan)
{
	double	radius;

	if (n_c.z >= 0 && n_c.z < mrt->cone[indx].height)
	{
		radius = n_c.z * tan;
		if (int_pow(n_c.x, 2) + int_pow(n_c.y, 2)
			< int_pow(radius, 2))
			return (1);
	}
	return (0);
}
