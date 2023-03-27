/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:33:43 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/26 20:30:42 by yridgway         ###   ########.fr       */
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
