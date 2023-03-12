/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:55:19 by ana               #+#    #+#             */
/*   Updated: 2023/03/12 22:14:32 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

	i = -1;
	while (++i < mrt->obj_count[LIGHT])
	{
		if (((t_discr)(get_sph_dscr(vec_rest(mrt->cam.pos, mrt->light[i].pos), \
		dir, int_pow(0.2, 2)))).dscr >= 0.0)
			color = mrt->light[i].color;
	}
	return (color);
}
