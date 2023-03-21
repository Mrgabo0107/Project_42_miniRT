/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:33:43 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/19 22:57:12 by yoel             ###   ########.fr       */
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

t_rgb	mult_color(t_rgb color, double mult)
{
	t_rgb	ret;

	ret.r = color.r * mult;
	ret.g = color.g * mult;
	ret.b = color.b * mult;
	// ret = normalize_color(ret);
	return (ret);
}

t_rgb	add_color(t_rgb color1, t_rgb color2)
{
	t_rgb	ret;

	ret.r = color1.r + color2.r;
	ret.g = color1.g + color2.g;
	ret.b = color1.b + color2.b;
	// ret = normalize_color(ret);
	return (ret);
}
