/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 01:29:54 by yoel              #+#    #+#             */
/*   Updated: 2023/03/15 01:33:30 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	add_ambient(t_rgb color, t_rgb ctr, t_light amb)
{
	t_rgb	ratio;

	ratio = ft_make_rgb_ratio(ctr);
	color.r += amb.color.r * amb.ratio * ratio.r;
	color.g += amb.color.g * amb.ratio * ratio.g;
	color.b += amb.color.b * amb.ratio * ratio.b;
	return (color);
}

t_rgb	add_diffuse(t_inter *ctr, t_rgb color, t_vec to_light, t_light light)
{
	double	angle;
	t_rgb	ratio;

	angle = get_angle_between(ctr->norm, to_light);
	if (angle > PI / 2)
		angle = PI / 2;
	angle = 1 - angle / (PI / 2);
	ratio = ft_make_rgb_ratio(ctr->color);
	color.r += light.color.r * light.ratio * ratio.r * angle;
	color.g += light.color.g * light.ratio * ratio.g * angle;
	color.b += light.color.b * light.ratio * ratio.b * angle;
	return (color);
}

t_rgb	add_specular(t_inter *ctr, t_rgb color, t_vec h, t_light light)
{
	double	angle;

	angle = 0.3 * int_pow(max_v(0, dot_prod(h, ctr->norm)), 16);
	color.r += light.color.r * light.ratio * angle;
	color.g += light.color.g * light.ratio * angle;
	color.b += light.color.b * light.ratio * angle;
	return (color);
}
