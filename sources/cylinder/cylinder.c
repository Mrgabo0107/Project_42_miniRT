/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/01 23:57:18 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_cylinder(t_mrt *mrt, t_inter inter)
{
	
}

int	is_in_cap(double curr, t_cylinder cyl, t_new_bas bas)
{
	if (int_pow(bas.new_cam.x + (curr * bas.new_dirc.x), 2)
		+ int_pow(bas.new_cam.y + (curr * bas.new_dirc.y), 2)
		<= int_pow(cyl.radius, 2))
		return (1);
	return (0);
}

double	get_dist_to_cyl(t_cylinder cyl, t_new_bas bas)
{
	double	curr;
	double	ret;

	ret = -1;
	if (v_abs(bas.new_dirc.z) > 0.0001)
	{ 
		curr = ((cyl.height / (2 * bas.new_dirc.z))
				- (bas.new_cam.z / bas.new_dirc.z));
		if (is_in_cap(curr, cyl, bas))
			ret = curr;
		curr = (-(cyl.height / (2 * bas.new_dirc.z))
				- (bas.new_cam.z / bas.new_dirc.z));
		if (is_in_cap(curr, cyl, bas) && curr < ret)
			ret = curr;
	}
	
		
	
		
}

t_mtrx	init_base_mtrx(t_base base)
{
	t_mtrx ret;

	ret = fill_mtrx(fill_coord(base.n1.x, base.n2.x, base.n3.x),
		fill_coord(base.n1.y, base.n2.y, base.n3.y),
		fill_coord(base.n1.z, base.n2.z, base.n3.z));
	return (ret);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int			i;
	double		c;
	t_new_bas	info;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		info.new_cam = vec_rest(point, mrt->cylinder[i].pos);
		mrt->cylinder[i].base = get_cyl_base(mrt->cylinder[i].dir);
		info.chg_base = init_base_mtrx(mrt->cylinder[1].base);
		info.chg_base = invert_mtrx(info.chg_base);
		info.new_cam = mtrx_by_vec(info.chg_base, info.new_cam);
		info.new_dirc = mtrx_by_vec(info.chg_base, dir);
		c = get_dist_to_cyl(mrt->cylinder[1], info);
		if (c > 0 && (ctrl->dist == -1 || c < ctrl->dist))
		{
			*ctrl = (t_inter){CYLINDER, i, c, \
			vec_sum(point, scal_vec(c, dir)), fill_coord(0, 0, 0)};
		}
		i++;
	}
}
