/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/02 04:46:15 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_discr	get_cyl_disc(t_cylinder cyl, t_vec new_cam, t_vec new_dirc)
{
	t_discr	ret;

	ret.a = int_pow(new_dirc.x, 2) + int_pow(new_dirc.y, 2);
	ret.b = 2 * ((new_cam.x * new_dirc.x)
			+ (new_cam.y * new_dirc.y));
	ret.c = int_pow(new_cam.x, 2) + int_pow(new_cam.y, 2)
		- int_pow(cyl.radius, 2);
	ret.dscr = int_pow(ret.b, 2) - (4 * (ret.a * ret.c));
	return (ret);
}

int	is_in_cap(double curr, t_cylinder cyl, t_vec new_cam, t_vec new_dirc)
{
	if (int_pow(new_cam.x + (curr * new_dirc.x), 2)
		+ int_pow(new_cam.y + (curr * new_dirc.y), 2)
		<= int_pow(cyl.radius, 2))
		return (1);
	return (0);
}

t_cyl_ctrl	check_cyl_body(t_cyl_ctrl *curr, t_cylinder cyl, t_vec nc, t_vec nd)
{
	t_cyl_ctrl	ret;
	t_discr		discr;
	double		curre;

	ret = *curr;
	discr = get_cyl_disc(cyl, nc, nd);
	if (discr.dscr >= 0.0)
	{
		curre = solve_quad(&discr);
		if (curre > 0 && (ret.c == -1 || curre < ret.c))
		{
			ret.c = curre;
			ret.cap_ctrl = 3;
		}
	}
	return (ret);
}

t_cyl_ctrl	get_dist_to_cyl(t_cylinder cyl, t_vec new_cam, t_vec new_dirc)
{
	double		curr;
	t_cyl_ctrl	ret;

	ret.c = -1;
	ret.cap_ctrl = 0;
	if (v_abs(new_dirc.z) > 0.0001)
	{
		curr = ((cyl.height / (2 * new_dirc.z))
				- (new_cam.z / new_dirc.z));
		if (curr > 0 && is_in_cap(curr, cyl, new_cam, new_dirc))
		{
			ret.c = curr;
			ret.cap_ctrl = 1;
		}
		curr = (-(cyl.height / (2 * new_dirc.z))
				- (new_cam.z / new_dirc.z));
		if (curr > 0 && is_in_cap(curr, cyl, new_cam, new_cam)
			&& (ret.c == -1 || curr < ret.c))
		{
			ret.c = curr;
			ret.cap_ctrl = 2;
		}
	}
	ret = check_cyl_body(&ret, cyl, new_cam, new_dirc);
	return (ret);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir)
{
	int				i;
	t_cyl_ctrl		ctr;
	t_vec			new_cam;
	t_vec			new_dirc;
	t_mtrx			chg_base;

	i = 0;
	while (i < mrt->obj_count[CYLINDER])
	{
		new_cam = vec_rest(point, mrt->cylinder[i].pos);
		mrt->cylinder[i].base = get_cyl_base(mrt->cylinder[i].dir);
		printf("created basis\n");
		print_vector(mrt->cylinder[i].base.n1);
		print_vector(mrt->cylinder[i].base.n2);
		print_vector(mrt->cylinder[i].base.n3);
		chg_base = init_base_mtrx(&mrt->cylinder[i].base);
		printf("first vector\n");
		// print_mtrx(info.chg_base);
		print_vector(chg_base.r1);
		printf("\n");
		chg_base = invert_mtrx(chg_base);
		new_cam = mtrx_by_vec(chg_base, new_cam);
		new_dirc = mtrx_by_vec(chg_base, dir);
		ctr = get_dist_to_cyl(mrt->cylinder[i], new_cam, new_dirc);
		if (ctr.c > 0 && (ctrl->dist == -1 || ctr.c < ctrl->dist))
		{
			*ctrl = (t_inter){CYLINDER, i, ctr.c, \
			vec_sum(point, scal_vec(ctr.c, dir)), fill_coord(0, 0, 0), \
			ctr.cap_ctrl};
		}
		i++;
	}
}
