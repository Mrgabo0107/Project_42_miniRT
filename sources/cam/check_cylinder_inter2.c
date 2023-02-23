/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_inter2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 05:14:06 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/23 07:07:13 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_discr	get_cyl_dscr(t_cylval vl, t_cylinder *cyl)
{
	t_discr	ret;

	ret.b = 2 * (vl.Ax * vl.Bx + vl.Ay * vl.By + vl.Az * vl.Bz);
	ret.a = int_pow(vl.Ax, 2) + int_pow(vl.Ay, 2) + int_pow(vl.Az, 2);
	ret.c = int_pow(vl.Bx, 2) + int_pow(vl.By, 2) + int_pow(vl.Bz, 2)
		- int_pow(cyl->radius, 2);
	ret.dscr = int_pow(ret.b, 2) - 4 * (ret.a * ret.c);
	return (ret);
}

static void	fill_cylval(t_cylval *val, t_cylinder cyl, t_vec *dir, t_mrt *mrt)
{
	val->Ax = dir->x - cyl.dir.x * (pnt_prod(cyl.dir, *dir));
	val->Ay = dir->y - cyl.dir.y * (pnt_prod(cyl.dir, *dir));
	val->Ax = dir->z - cyl.dir.z * (pnt_prod(cyl.dir, *dir));
	val->Bx = mrt->cam.pos.x - cyl.pos.x - cyl.dir.x
		* (pnt_prod(cyl.dir, vec_rest(mrt->cam.pos, cyl.pos)));
	val->By = mrt->cam.pos.y - cyl.pos.y - cyl.dir.y
		* (pnt_prod(cyl.dir, vec_rest(mrt->cam.pos, cyl.pos)));
	val->Bz = mrt->cam.pos.z - cyl.pos.z - cyl.dir.z
		* (pnt_prod(cyl.dir, vec_rest(mrt->cam.pos, cyl.pos)));
}

static double	solve_cyl_quad(t_discr *info)
{
	double	op1;
	double	op2;
	double	ret;

	if (info->dscr == 0.0)
		return (-info->b / (2 * info->a));
	op1 = (-info->b + sqrt(info->dscr)) / (2 * info->a);
	op2 = (-info->b - sqrt(info->dscr)) / (2 * info->a);
	ret = min_v(op1, op2);
	if (ret < 0)
		return (max_v(op1, op2));
	return (ret);
}

static int	lim_cond(t_mrt *mrt, double c, t_inter ctrl, int i)
{
	double	half_h;
	double	val;

	half_h = mrt->cylinder[i].height / 2;
	val = c * (pnt_prod(mrt->cylinder[i].dir, ctrl.pxl))
		+ (pnt_prod(mrt->cylinder[i].dir,
				vec_rest(mrt->cam.pos, mrt->cylinder[i].pos)));
	printf("val = %f, half_h = %f\n", val, half_h);
	if(-half_h <= val && val <= half_h)
		return (1);
	return (0);
}

void	check_cyl_body(t_mrt *mrt, t_inter *ctrl, int i, t_vec *dir)
{
	t_cylval	val;
	double		c;
	t_discr		discr;

	fill_cylval(&val, mrt->cylinder[i], dir, mrt);
	discr = get_cyl_dscr(val, &mrt->cylinder[i]);
	if (discr.dscr >= 0)
	{
		printf("para %f ", discr.dscr);
		c = solve_cyl_quad(&discr);
		printf("c = %f ", c);
		if (c >= 0 && lim_cond(mrt, c, *ctrl, i)
			&& (ctrl->dist == -1 || c < ctrl->dist))
		{
			ctrl->type = CYLINDER;
			ctrl->index = i;
			ctrl->dist = c;
			ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vector(c, *dir));
		}
	}
}
