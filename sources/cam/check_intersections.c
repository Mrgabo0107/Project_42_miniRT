/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/22 01:30:43 by gamoreno         ###   ########.fr       */
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
			c = min_v((-discr.b + discr.dscr) / discr.a,
				(-discr.b - discr.dscr) / discr.a);
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