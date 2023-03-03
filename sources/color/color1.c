/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/03 17:52:49 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	ft_make_rgb(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

float	get_angle_between(t_vec v1, t_vec v2)
{
	float	angle;

	if (vect_norm(v1) == 0 || vect_norm(v2) == 0)
		return (0);
	angle = acos(dot_prod(v1, v2) / (vect_norm(v1) * vect_norm(v2)));
	return (angle);
}

t_vec	vec_mult(t_vec vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	return (vec);
}

t_inter	check_shaddow(t_mrt *mrt, t_inter *ctr, t_vec dir, double len)
{
	t_inter	ret;
	t_vec	point;

	point = vec_sum(ctr->inter_coor, vec_mult(ctr->norm, 0.0000001));
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

// t_rgb	add_ambient(t_rgb color, t_light amb)
// {
// 	color.r += amb.color.r * amb.ratio;
// 	color.g += amb.color.g * amb.ratio;
// 	color.b += amb.color.b * amb.ratio;
// 	return (color);
// }

t_rgb	ft_make_rgb_ratio(t_rgb color, float ratio)
{
	color.r = color.r / 255 * ratio;
	color.g = color.g / 255 * ratio;
	color.b = color.b / 255 * ratio;
	return (color);
}

t_rgb	diminish_color(t_inter *ctr, t_vec to_light, t_light light)
{
	double	angle;
	t_rgb	color;
	t_rgb	ratio;

	angle = get_angle_between(ctr->norm, to_light);
	if (angle > PI / 2)
		angle = PI / 2;
	ratio = ft_make_rgb_ratio(ctr->color, 1 - angle / (PI / 2));
	color.r = light.color.r * light.ratio * ratio.r;//light.ratio + ctr->color.r * (angle / (PI / 2));
	color.g = light.color.g * light.ratio * ratio.g;//light.ratio + ctr->color.g * (angle / (PI / 2));
	color.b = light.color.b * light.ratio * ratio.b;//light.ratio + ctr->color.b * (angle / (PI / 2));
	return (color);
}

double	mult_max(double a, double b, double c)
{
	double	max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return (max);
}

t_rgb	add_ambient(t_rgb color, t_rgb ctr, t_light amb)
{
	double	max;

	color.r += amb.color.r * amb.ratio;
	color.g += amb.color.g * amb.ratio;
	color.b += amb.color.b * amb.ratio;
	max = mult_max(color.r, color.g, color.b);
	if (max > 255)
	{
		// printf("1: %f %f %f\n", color.r, color.g, color.b);
		color.r *= 255 / max;
		color.g *= 255 / max;
		color.b *= 255 / max;
		// printf("2: %f %f %f\n", color.r, color.g, color.b);
	}
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
			color = diminish_color(ctr, coor_to_light, mrt->light);
		color = add_ambient(color, ctr->color, mrt->amblight);
	}
	if (((t_discr)(get_sph_dscr(vec_rest(mrt->cam.pos, mrt->light.pos), \
	dir, int_pow(0.2, 2)))).dscr >= 0.0)
		color = ft_make_rgb(255, 255, 255);
	return (color);
}
