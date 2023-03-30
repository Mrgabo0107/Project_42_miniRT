/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:55:19 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/31 00:14:16 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_angle_between(t_vec v1, t_vec v2)
{
	double	angle;

	if (vect_norm(v1) == 0 || vect_norm(v2) == 0)
		return (0);
	angle = acos(dot_prod(v1, v2) / (vect_norm(v1) * vect_norm(v2)));
	return (angle);
}

t_rgb	ft_make_rgb_ratio(t_rgb color)
{
	color.r = color.r / 255;
	color.g = color.g / 255;
	color.b = color.b / 255;
	return (color);
}

t_rgb	normalize_color(t_rgb color)
{
	double	max;

	max = color.r;
	if (color.g > max)
		max = color.g;
	if (color.b > max)
		max = color.b;
	if (max > 255)
	{
		color.r *= 255 / max;
		color.g *= 255 / max;
		color.b *= 255 / max;
	}
	return (color);
}

t_rgb	ft_make_rgb(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_rgb	show_light_sources(t_mrt *mrt, t_rgb color, t_vec dir)
{
	int		i;
	t_vec	cam_to_light;
	t_inter	linter;
	t_inter	ctr;
	t_discr	dscr;

	i = -1;
	ctr.inter_coor = mrt->cam.pos;
	ctr.norm = mrt->cam.dir;
	while (++i < mrt->obj_count[LIGHT])
	{
		cam_to_light = vec_rest(mrt->light[i].pos, mrt->cam.pos);
		linter = check_shaddow(mrt, &ctr, normalize(cam_to_light), \
		vect_norm(cam_to_light));
		if ((linter.dist < 0 || linter.dist > vect_norm(cam_to_light)))
		{
			dscr = get_sph_dscr(vec_rest(mrt->cam.pos, \
			mrt->light[i].pos), dir, int_pow(0.2, 2));
			if (dscr.dscr >= 0 && solve_quad(&dscr) > 0)
				color = mrt->light[i].color;
		}
	}
	return (color);
}
