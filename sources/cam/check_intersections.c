/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/22 14:58:06 by gamoreno         ###   ########.fr       */
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
	if (info->dscr == 0.0)
		return (-info->b / info->a);
	else if (info->dscr > 0.0)
		return (min_v((-info->b + sqrt(info->dscr)) / info->a,
			(-info->b - sqrt(info->dscr)) / info->a));
}

void	check_spheres(t_mrt *mrt, t_inter *ctrl)
{
	int		i;
	t_vec	dir;
	t_discr	discr;
	double	c;

	i = 0;
	dir = normalize(vec_sum(ctrl->pxl, scal_vector(-1, mrt->cam.pos)));
	while (&mrt->sphere[i])
	{
		discr = get_sph_dscr(mrt, &mrt->sphere[i], dir);
		if (discr.dscr >= 0)
		{
			c = solve_sph_quad(&discr);
			if (ctrl->dist == -1 || c < ctrl->dist)
			{
				ctrl->type = SPHERE;
				ctrl->index = i;
				ctrl->dist = c;
				ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vector(c, dir));
			}
		}
		i++;
	}
}