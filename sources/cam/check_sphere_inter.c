/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere_inter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/28 20:46:46 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_discr	get_sph_dscr(t_vec point, t_sphere *sph, t_vec dir)
{
	t_discr	ret;

	ret.b = dot_prod(dir, vec_rest(point, sph->center));
	ret.a = norm_raised_2(dir);
	ret.c = norm_raised_2(vec_rest(point, sph->center))
		- int_pow(sph->radius, 2);
	ret.dscr = 4 * (int_pow(ret.b, 2) - (ret.a * ret.c));
	return (ret);
}

static double	solve_sph_quad(t_discr *info)
{
	double	op1;
	double	op2;
	double	ret;

	if (info->dscr == 0.0)
		return (-info->b / info->a);
	op1 = (-info->b + sqrt(info->dscr)) / info->a;
	op2 = (-info->b - sqrt(info->dscr)) / info->a;
	ret = min_v(op1, op2);
	if (ret < 0)
		return (max_v(op1, op2));
	return (ret);
}

void	check_spheres(t_mrt *mrt, t_vec point, t_inter *ctrl, t_vec dir)
{
	int		i;
	t_discr	discr;
	double	c;

	i = 0;
	while (i < mrt->obj_count[SPHERE])
	{
		discr = get_sph_dscr(point, &mrt->sphere[i], dir);
		if (discr.dscr >= 0)
		{
			c = solve_sph_quad(&discr);
			if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
				*ctrl = (t_inter){ctrl->pxl, SPHERE, i, c, \
				vec_sum(point, scal_vec(c, dir)), \
				vec_rest(vec_sum(point, scal_vec(c, dir)), \
				mrt->sphere[i].center)};
		}
		i++;
	}
}
