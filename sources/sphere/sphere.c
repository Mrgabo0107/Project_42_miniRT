/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/01 22:10:56 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_sphere(t_mrt *mrt, t_inter inter)
{
	return (normalize(vec_rest(inter.inter_coor, \
	mrt->sphere[inter.index].center)));
}

t_discr	get_sph_dscr(t_vec ncam, t_vec dir, double square_rad)
{
	t_discr	ret;

	ret.a = norm_raised_2(dir);
	ret.b = 2 * (dot_prod(ncam, dir));
	ret.c = norm_raised_2(ncam) - square_rad;
	ret.dscr = int_pow(ret.b, 2) - (4 * (ret.a * ret.c));
	return (ret);
}

static double	solve_sph_quad(t_discr *info)
{
	double	op1;
	double	op2;
	double	ret;

	if (info->dscr < 0.00001)
		return (-info->b / (2 * info->a));
	op1 = (-info->b + sqrt(info->dscr)) / (2 * info->a);
	op2 = (-info->b - sqrt(info->dscr)) / (2 * info->a);
	ret = min_v(op1, op2);
	if (ret < 0)
		return (max_v(op1, op2));
	return (ret);
}

void	check_spheres(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int		i;
	double	c;
	t_discr	discr;
	t_vec	new_cam;

	i = 0;
	while (i < mrt->obj_count[SPHERE])
	{
		new_cam = vec_rest(point, mrt->sphere[i].center);
		discr = get_sph_dscr(new_cam, dir, int_pow(mrt->sphere[i].radius, 2));
		if (discr.dscr >= 0.0)
		{
			c = solve_sph_quad(&discr);
			if (c > 0 && (ctrl->dist == -1 || c < ctrl->dist))
				*ctrl = (t_inter){SPHERE, i, c, vec_sum(vec_sum(new_cam, \
				scal_vec(c, dir)), mrt->sphere[i].center), fill_coord(0, 0, 0)};
		}
		i++;
	}
}
