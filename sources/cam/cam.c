/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:02:45 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/27 15:48 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_all_cam_values(t_cam *cam, int ix)
{
	double	aux_norm;
	double	sqr_sum1;
	double	sqr_sum2;

	cam->s_half_screen = tan(rad_and_deg(cam->fov / 2, 1));
	cam->step = cam->s_half_screen / ix;
	cam->screen_base.bs_orig = vec_sum(cam->pos, cam->dir);
	if (v_abs(cam->dir.x) < 0.00001 && v_abs(cam->dir.y) < 0.0001)
	{
		cam->screen_base.n1 = fill_coord(1, 0, 0);
		cam->screen_base.n2 = fill_coord(0, 1, 0);
		cam->screen_base.n3 = fill_coord(0, 0, cam->dir.z);
		return ;
	}
	sqr_sum1 = int_pow(cam->dir.x, 2) + int_pow(cam->dir.y, 2);
	aux_norm = sqrt(sqr_sum1);
	cam->screen_base.n1 = fill_coord(cam->dir.y / aux_norm,
			-cam->dir.x / aux_norm, 0);
	sqr_sum2 = int_pow(cam->dir.x * cam->dir.z, 2)
		+ int_pow(cam->dir.y * cam->dir.z, 2) + int_pow(sqr_sum1, 2);
	aux_norm = sqrt(sqr_sum2);
	cam->screen_base.n2 = fill_coord((cam->dir.x * cam->dir.z) / aux_norm,
			(cam->dir.y * cam->dir.z) / aux_norm, -sqr_sum1 / aux_norm);
	cam->screen_base.n3 = fill_coord(cam->dir.x, cam->dir.y, cam->dir.z);
}

t_vec	screen_pxl_by_indx(t_mrt *mrt, t_cam *cam, int i, int j)
{
	t_vec	res;
	double	scal_i;
	double	scal_j;

	scal_i = -cam->s_half_screen + (((2 * i) - 1) * cam->step);
	scal_j = ((-(double)mrt->iy / (double)mrt->ix) * cam->s_half_screen)
		+ (((2 * j) - 1) * cam->step);
	res = vec_sum(cam->screen_base.bs_orig,
			vec_sum(scal_vec(scal_i, cam->screen_base.n1),
				scal_vec(scal_j, cam->screen_base.n2)));
	return (res);
}
