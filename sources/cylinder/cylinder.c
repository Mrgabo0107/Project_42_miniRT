/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/01 19:56:04 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_cylinder(t_mtr, *mrt, t_inter inter)
{
}

t_mtrx	init_base_mtrx(t_base base)
{
	t_mtrx ret;

	ret = fill_mtrx(l);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int		i;
	double	c;
	t_vec	new_cam;
	t_vec	new_dirc;
	t_mtrx	chg_base;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		new_cam = vec_rest(point, mrt->cylinder[i].pos);
		mrt->cylinder[i].base = get_cyl_base(mrt->cylinder[i].dir);
		chg_base = init_base_mtrx(mrt->cylinder[1].base);
		chg_base = invert_mtrx(chg_base);
		if (c >= 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			*ctrl = (t_inter){CYLINDER, i, c, \
			vec_sum(mrt->cam.pos, scal_vec(c, dir)), fill_coord(0, 0, 0)};
		}
		i++;
	}
}
