/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/13 23:57:13 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	check_shaddow(t_mrt *mrt, t_inter *ctr, t_vec dir, double len)
{
	t_inter	ret;
	t_vec	point;

	point = vec_sum(ctr->inter_coor, scal_vec(0.0000001, ctr->norm));
	ret.type = UNDEFINED;
	ret.index = 0;
	ret.dist = -1;
	check_planes(mrt, &ret, point, dir);
	if (ret.dist != -1 && ret.dist < len)
		return (ret);
	check_spheres(mrt, &ret, point, dir);
	if (ret.dist != -1 && ret.dist < len)
		return (ret);
	check_cylinders(mrt, &ret, point, dir);
	return (ret);
}

t_rgb	add_ambient(t_rgb color, t_rgb ctr, t_light amb)
{
	t_rgb	ratio;

	ratio = ft_make_rgb_ratio(ctr);
	color.r += amb.color.r * amb.ratio * ratio.r;
	color.g += amb.color.g * amb.ratio * ratio.g;
	color.b += amb.color.b * amb.ratio * ratio.b;
	return (color);
}

t_rgb	add_color(t_inter *ctr, t_rgb color, t_vec to_light, t_light light)
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

	angle = 0.2 * int_pow(max_v(0, dot_prod(h, ctr->norm)), 32);
	color.r += light.color.r * light.ratio * angle;
	color.g += light.color.g * light.ratio * angle;
	color.b += light.color.b * light.ratio * angle;
	return (color);
}

t_rgb	get_color(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	t_rgb	color;
	t_vec	coor_to_light;
	t_inter	linter;
	int		i;

	i = -1;
	color = ft_make_rgb(0, 0, 0);
	if (ctr->dist != -1)
	{
		while (++i < mrt->obj_count[LIGHT])
		{
			coor_to_light = vec_rest(mrt->light[i].pos, ctr->inter_coor);
			linter = check_shaddow(mrt, ctr, normalize(coor_to_light), \
			vect_norm(coor_to_light));
			if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
			{
				color = add_color(ctr, color, coor_to_light, mrt->light[i]);
				color = add_specular(ctr, color, \
				scal_vec(1 / vect_norm(vec_sum(coor_to_light, \
				vec_rest(mrt->cam.pos, ctr->inter_coor))), \
				vec_sum(coor_to_light, vec_rest(mrt->cam.pos, \
				ctr->inter_coor))), mrt->light[i]);
			}
		}
		color = add_ambient(color, ctr->color, mrt->amblight);
	}
	color = show_light_sources(mrt, color, dir);
	color = normalize_color(color);
	return (color);
}
