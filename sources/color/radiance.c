/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 01:29:54 by yoel              #+#    #+#             */
/*   Updated: 2023/03/19 23:25:34 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_ambient(t_rgb ctr, t_light amb, double mirror)
{
	t_rgb	ratio;
	t_rgb	color;

	ratio = ft_make_rgb_ratio(ctr);
	color.r = amb.color.r * amb.ratio * ratio.r * mirror;
	color.g = amb.color.g * amb.ratio * ratio.g * mirror;
	color.b = amb.color.b * amb.ratio * ratio.b * mirror;
	return (color);
}

t_rgb	get_diffuse(t_inter *ctr, t_vec to_light, t_light light)
{
	double	angle;
	t_rgb	ratio;
	t_rgb	color;

	angle = get_angle_between(ctr->norm, to_light);
	if (angle > PI / 2)
		angle = PI / 2;
	angle = 1 - angle / (PI / 2);
	ratio = ft_make_rgb_ratio(ctr->color);
	color.r = light.color.r * light.ratio * ratio.r * angle;
	color.g = light.color.g * light.ratio * ratio.g * angle;
	color.b = light.color.b * light.ratio * ratio.b * angle;
	return (color);
}

t_rgb	get_specular(t_inter *ctr, t_vec pos, t_vec to_light, t_light light)
{
	double	angle;
	t_rgb	color;
	t_vec	h;

	h = scal_vec(1 / vect_norm(vec_sum(to_light, \
	vec_rest(pos, ctr->inter_coor))), vec_sum(to_light, \
	vec_rest(pos, ctr->inter_coor)));
	angle = 0.3 * int_pow(max_v(0, dot_prod(h, ctr->norm)), 16);
	color.r = light.color.r * light.ratio * angle;
	color.g = light.color.g * light.ratio * angle;
	color.b = light.color.b * light.ratio * angle;
	return (color);
}
