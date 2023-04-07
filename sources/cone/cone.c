/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:11:17 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 04:01:24gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_discr	get_cone_disc(t_vec *f_n, double tan)
{
	t_discr	ret;

	ret.a = int_pow(f_n[1].x, 2) + int_pow(f_n[1].y, 2) \
	- int_pow((f_n[1].z * tan), 2);
	ret.b = 2 * ((f_n[0].x * f_n[1].x) + (f_n[0].y * f_n[1].y) \
	- (f_n[0].z * f_n[1].z * int_pow(tan, 2)));
	ret.c = int_pow(f_n[0].x, 2) + int_pow(f_n[0].y, 2) \
	- int_pow((f_n[0].z * tan), 2);
	ret.dscr = int_pow(ret.b, 2) - (4 * (ret.a * ret.c));
	return (ret);
}

int	is_in_top(double *curr_tan, t_cone cone, t_vec new_cam, t_vec new_dir)
{
	double	radius;

	radius = cone.height * curr_tan[1];
	if (int_pow(new_cam.x + (curr_tan[0] * new_dir.x), 2)
		+ int_pow(new_cam.y + (curr_tan[0] * new_dir.y), 2)
		<= int_pow(radius, 2))
		return (1);
	return (0);
}

t_cuad_ctr	check_cone_body(t_cuad_ctr *crr, t_cone cone, \
t_vec *f_n, double tan)
{
	t_cuad_ctr	ret;
	t_discr		discr;
	double		curr;
	t_vec		h_ctrl;

	ret = *crr;
	discr = get_cone_disc(f_n, tan);
	if (discr.dscr >= 0.0)
	{
		curr = solve_cone_quad(&discr, f_n);
		if (curr > 0 && (ret.c == -1 || curr < ret.c))
		{
			h_ctrl = vec_sum(f_n[0], scal_vec(curr, f_n[1]));
			if (0 <= h_ctrl.z && h_ctrl.z <= cone.height)
			{
				ret.c = curr;
				ret.cap_ctrl = 2;
			}
		}
	}
	return (ret);
}

t_cuad_ctr	get_dist_to_cone(t_cone cone, t_vec n_c, t_vec n_d, double tang)
{
	t_cuad_ctr	ret;
	double		curr_tan[2];
	t_vec		fuck_normntte[2];

	curr_tan[1] = tang;
	ret.c = -1;
	ret.cap_ctrl = 0;
	if (v_abs(n_d.z) > 0.0001)
	{
		curr_tan[0] = ((cone.height / n_d.z) - (n_c.z / n_d.z));
		if (curr_tan[0] > 0 && is_in_top(curr_tan, cone, n_c, n_d)
			&& (ret.c == -1 || curr_tan[0] < ret.c))
		{
			ret.c = curr_tan[0];
			ret.cap_ctrl = 1;
		}
	}
	fuck_normntte[0] = n_c;
	fuck_normntte[1] = n_d;
	ret = check_cone_body(&ret, cone, fuck_normntte, curr_tan[1]);
	return (ret);
}

void	check_cones(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int				i;
	t_cuad_ctr		ctr;
	t_vec			new[2];
	double			tang;
	t_mtrx			chg_base;

	i = -1;
	while (++i < mrt->obj_count[CONE])
	{
		tang = tan(mrt->cone[i].angle / 2);
		new[0] = vec_rest(point, mrt->cone[i].pos);
		chg_base = fill_mtrx(mrt->cone[i].base.n1, mrt->cone[i].base.n2,
				mrt->cone[i].base.n3);
		new[0] = mtrx_by_vec(chg_base, new[0]);
		new[1] = mtrx_by_vec(chg_base, dir);
		ctr = get_dist_to_cone(mrt->cone[i], new[0], new[1], tang);
		if (ctr.c > 0 && (ctrl->dist == -1 || ctr.c < ctrl->dist))
		{
			*ctrl = (t_inter){CONE, i, ctr.c, vec_sum(point, \
			scal_vec(ctr.c, dir)), fill_coord(0, 0, 0), \
			get_cone_color(mrt, i, new, ctr), mrt->cone[i].option, \
			ctr.cap_ctrl, cam_in_cone(mrt, i, new[0], tang)};
			ctrl->color = get_cone_texture(mrt, *ctrl);
		}
	}
}

