/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/04 14:40:29 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_angle_between(t_vec v1, t_vec v2)
{
	float	angle;

	if (vect_norm(v1) == 0 || vect_norm(v2) == 0)
		return (0);
	angle = acos(dot_prod(v1, v2) / (vect_norm(v1) * vect_norm(v2)));
	return (angle);
}

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
	color = normalize_color(color);
	return (color);
}

t_rgb	add_color(t_inter *ctr, t_vec to_light, t_light light)
{
	double	angle;
	t_rgb	color;
	t_rgb	ratio;

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

t_rgb	get_color(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	t_rgb	color;
	t_vec	coor_to_light;
	t_inter	linter;

	color = ft_make_rgb(0, 0, 0);
	if (ctr->dist != -1)
	{
		coor_to_light = vec_rest(mrt->light.pos, ctr->inter_coor);
		linter = check_shaddow(mrt, ctr, normalize(coor_to_light), \
		vect_norm(coor_to_light));
		if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
			color = add_color(ctr, coor_to_light, mrt->light);
		color = add_ambient(color, ctr->color, mrt->amblight);
	}
	if (((t_discr)(get_sph_dscr(vec_rest(mrt->cam.pos, mrt->light.pos), \
	dir, int_pow(0.2, 2)))).dscr >= 0.0)
		color = mrt->light.color;
	return (color);
}
