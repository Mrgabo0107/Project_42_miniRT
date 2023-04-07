/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:31:29 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 16:38:42 by yridgway         ###   ########.fr       */
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
	if (mrt->sphere[inter.index].option.b_mp_ctrl == 1)
		ret = sphere_bumped(mrt, inter, ret);
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

t_rgb	get_sphere_texture(t_mrt *mrt, t_inter inter)
{
	t_mtrx	chg;
	t_vec	new_inter;
	int		bump_coor[2];
	double	res[2];
	t_rgb	color;

	if (!mrt->sphere[inter.index].option.texture_ctrl)
		return (inter.color);
	chg = fill_mtrx(mrt->sphere[inter.index].base.n1,
			mrt->sphere[inter.index].base.n2,
			mrt->sphere[inter.index].base.n3);
	new_inter = vec_rest(inter.inter_coor, mrt->sphere[inter.index].center);
	new_inter = mtrx_by_vec(chg, new_inter);
	new_inter = get_spheric_coord(new_inter);
	res[0] = PI / mrt->sphere[inter.index].option.texture.height;
	res[1] = (2 * PI) / (mrt->sphere[inter.index].option.texture.width - 1);
	bump_coor[0] = (int)integer_part(new_inter.y / res[0]);
	bump_coor[1] = (int)integer_part(new_inter.z / res[1]);
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->sphere[inter.index].option.texture.array \
	[bump_coor[0]][bump_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

void	check_spheres(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int		i;
	double	c;
	t_discr	discr;
	t_vec	new_cam;

	i = -1;
	while (++i < mrt->obj_count[SPHERE])
	{
		new_cam = vec_rest(point, mrt->sphere[i].center);
		discr = get_sph_dscr(new_cam, dir, int_pow(mrt->sphere[i].radius, 2));
		if (discr.dscr >= 0.0)
		{
			c = solve_quad(&discr);
			if (c > 0 && (ctrl->dist == -1 || c < ctrl->dist))
			{
				*ctrl = (t_inter){SPHERE, i, c, vec_sum(point, \
				scal_vec(c, dir)), fill_coord(0, 0, 0), \
				get_sphere_color(mrt, i, \
				vec_sum(point, scal_vec(c, dir))), \
				mrt->sphere[i].option, 0, \
				cam_in_sph(mrt, i, new_cam)};
				ctrl->color = get_sphere_texture(mrt, *ctrl);
			}
		}
	}
}
