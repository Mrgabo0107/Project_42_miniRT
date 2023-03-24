/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:55:19 by ana               #+#    #+#             */
/*   Updated: 2023/03/24 22:28:47 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_opposite_color(t_rgb color)
{
	t_rgb	ret;

	ret.r = 255 - color.r;
	ret.g = 255 - color.g;
	ret.b = 255 - color.b;
	ret = normalize_color(ret);
	return (ret);
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
