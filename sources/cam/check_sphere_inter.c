/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere_inter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/23 18:58:18 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_discr get_sph_dscr(t_mrt *mrt, t_sphere *sph, t_vec dir)
{
	t_discr	ret;

	ret.b = dir.x * (mrt->cam.pos.x - sph->center.x)
		+ dir.y * (mrt->cam.pos.y - sph->center.y)
		+ dir.z * (mrt->cam.pos.z - sph->center.z);
	ret.a = int_pow(dir.x, 2) + int_pow(dir.y, 2) + int_pow(dir.z, 2);
	ret.c = int_pow(mrt->cam.pos.x - sph->center.x, 2)
		+ int_pow(mrt->cam.pos.y - sph->center.y, 2)
		+ int_pow(mrt->cam.pos.z - sph->center.z, 2)
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

void	check_spheres(t_mrt *mrt, t_inter *ctrl)
{
	int		i;
	t_vec	dir;
	t_discr	discr;
	double	c;

	i = 0;
	dir = normalize(vec_sum(ctrl->pxl, scal_vector(-1, mrt->cam.pos)));
	while (i < mrt->obj_count[SPHERE])
	{
		discr = get_sph_dscr(mrt, &mrt->sphere[i], dir);
		if (discr.dscr >= 0)
		{
			c = solve_sph_quad(&discr);
			if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
			{
				ctrl->type = SPHERE;
				ctrl->index = i;
				ctrl->dist = c;
				ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vector(c, dir));
				// printf("plane inter coor: %f, %f, %f\n", ctrl->inter_coor.x, ctrl->inter_coor.y, ctrl->inter_coor.z);
			}
		}
		i++;
	}
}