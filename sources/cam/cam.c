/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:02:45 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/24 05:31:11 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_all_cam_values(t_cam *cam)
{
	double	aux_norm;
	double	sqr_sum1;
	double	sqr_sum2;

	cam->s_half_screen = tan(rad_and_deg(cam->fov / 2, 1));
	cam->step =  cam->s_half_screen / WX;
	cam->screen_base.bs_orig = vec_sum(cam->pos, cam->dir);
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

t_vec	screen_pxl_by_indx(t_cam *cam, int i, int j)
{
	t_vec	res;
	double	scal_i;
	double	scal_j;

	scal_i = -cam->s_half_screen + (((2 * i) - 1) * cam->step);
	scal_j = ((-(double)WY / (double)WX) * cam->s_half_screen) + (((2 * j) - 1) * cam->step);
	res = vec_sum(cam->screen_base.bs_orig, vec_sum(scal_vec(scal_i, cam->screen_base.n1)
		, scal_vec(scal_j, cam->screen_base.n2)));
	return (res);
}

/*for debugging*/
void print_pixels_coord(t_cam *cam)
{
	int	i;
	int	j;
	t_vec	aux;

	j = 1;
	while (j <= WY)
	{
		i = 1;
		while (i <= WX)
		{
			aux = screen_pxl_by_indx(cam, i, j);
			print_vector(aux);
			i++;
		}
		printf("\n");
		j++;
	}
}