/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:33:43 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/29 22:00:47 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_opposite_color(t_rgb color)
{
	t_rgb	ret;

	ret.r = 255 - color.r;
	ret.g = 255 - color.g;
	ret.b = 255 - color.b;
	return (ret);
}

t_rgb	mult_color(t_rgb color, double mult)
{
	t_rgb	ret;

	ret.r = color.r * mult;
	ret.g = color.g * mult;
	ret.b = color.b * mult;
	return (ret);
}

t_rgb	add_color(t_rgb color1, t_rgb color2)
{
	t_rgb	ret;

	ret.r = color1.r + color2.r;
	ret.g = color1.g + color2.g;
	ret.b = color1.b + color2.b;
	return (ret);
}

int	diminish_color(int color, double percent)
{
	t_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	rgb = mult_color(rgb, percent);
	return ((int)rgb.r << 16 | (int)rgb.g << 8 | (int)rgb.b);
}

t_rgb	convert_to_rgb(int color)
{
	t_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}
