/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/23 04:05:29 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cam_in_sph(t_mrt *mrt, int index, t_vec new_cam)
{
	if (mrt->sphere[index].radius >= vect_norm(new_cam))
		return (1);
	return (0);
}

t_vec	get_normal_sphere(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = normalize(vec_rest(inter.inter_coor,
				mrt->sphere[inter.index].center));
	if (inter.is_in_obj)
		ret = scal_vec(-1, ret);
	return (ret);
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
			c = solve_quad(&discr);
			if (c > 0 && (ctrl->dist == -1 || c < ctrl->dist))
				*ctrl = (t_inter){SPHERE, i, c, vec_sum(point, \
				scal_vec(c, dir)), fill_coord(0, 0, 0), \
				get_sphere_color(mrt, i, \
				vec_sum(point, scal_vec(c, dir))), \
				mrt->sphere[i].option, 0, \
				cam_in_sph(mrt, i, new_cam)};
		}
		i++;
	}
}
