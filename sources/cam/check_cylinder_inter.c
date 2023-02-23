/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_inter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/23 05:35:19 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	case1(t_mrt *mrt, t_inter *ctrl, int i, t_vec *dir)
{
	double	c;
	double	half_h;

	half_h = mrt->cylinder[i].height / 2;
	c = pnt_prod(mrt->cylinder[i].dir, vec_rest(mrt->cylinder[i].pos,
				vec_sum(mrt->cam.pos, scal_vector(half_h,
						mrt->cylinder[i].dir))))
		/ pnt_prod(mrt->cylinder[i].dir, ctrl->pxl);
	if (c >= 0 && vect_norm(vec_rest(vec_sum(mrt->cam.pos,
					scal_vector(c, ctrl->pxl)), vec_sum(mrt->cylinder[i].pos,
					scal_vector(half_h, mrt->cylinder[i].dir))))
		<= mrt->cylinder[i].radius
		&& (ctrl->dist == -1 || c < ctrl->dist))
	{
		ctrl->type = CYLINDER;
		ctrl->index = i;
		ctrl->dist = c;
		ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vector(c, *dir));
	}
}

static void	case2(t_mrt *mrt, t_inter *ctrl, int i, t_vec *dir)
{
	double	c;
	double	half_h;

	half_h = mrt->cylinder[i].height / 2;
	c = pnt_prod(mrt->cylinder[i].dir, vec_rest(mrt->cylinder[i].pos,
				vec_sum(mrt->cam.pos, scal_vector(-half_h,
						mrt->cylinder[i].dir))))
		/ pnt_prod(mrt->cylinder[i].dir, ctrl->pxl);
	if (c >= 0 && vect_norm(vec_rest(vec_sum(mrt->cam.pos,
					scal_vector(c, ctrl->pxl)), vec_sum(mrt->cylinder[i].pos,
					scal_vector(-half_h, mrt->cylinder[i].dir))))
		<= mrt->cylinder[i].radius
		&& (ctrl->dist == -1 || c < ctrl->dist))
	{
		ctrl->type = CYLINDER;
		ctrl->index = i;
		ctrl->dist = c;
		ctrl->inter_coor = vec_sum(mrt->cam.pos, scal_vector(c, *dir));
	}
}

static void	check_cyl_ends(t_mrt *mrt, t_inter *ctrl, int i, t_vec *dir)
{
	case1(mrt, ctrl, i, dir);
	case2(mrt, ctrl, i, dir);
}

void	check_cylinders(t_mrt *mrt, t_inter *ctrl)
{
	int		i;
	t_vec	dir;

	i = 0;
	dir = normalize(vec_sum(ctrl->pxl, scal_vector(-1, mrt->cam.pos)));
	while (i < mrt->obj_count[CYLINDER])
	{
		check_cyl_ends(mrt, ctrl, i, &dir);
		check_cyl_body(mrt, ctrl, i, &dir);
		i++;
	}
}
