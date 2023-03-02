/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/02 23:48:57 by ana              ###   ########.fr       */
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

t_rgb	add_ambient(t_rgb color, t_rgb amb, double ratio)
{
	color.r -= amb.r * ratio;
	color.g -= amb.g * ratio;
	color.b -= amb.b * ratio;
	if (color.r < 0 || color.g < 0 || color.b < 0)
		printf("r: %d, g: %d, b: %d\n", color.r, color.g, color.b);
	if (color.r < 0)
		color.r = 0;
	if (color.g < 0)
		color.g = 0;
	if (color.b < 0)
		color.b = 0;
	return (color);
}

t_rgb	diminish_color(t_rgb color, t_vec vec1, t_vec vec2, t_light amb)
{
	double	angle;
	double	ratio;
	t_rgb	new_color;

	angle = get_angle_between(vec1, vec2);
	if (angle > PI / 2)
		angle = PI / 2;
	ratio = angle / (PI / 2);
	new_color.r = color.r - color.r * ratio;// + amb.r;
	new_color.g = color.g - color.g * ratio;// + amb.g;
	new_color.b = color.b - color.b * ratio;// + amb.b;
	// if (new_color.r > 255)
	// 	new_color.r = 255;
	// if (new_color.g > 255)
	// 	new_color.g = 255;
	// if (new_color.b > 255)
	// 	new_color.b = 255;
	// if (new_color.r < amb.color.r * (1 - amb.ratio) && \
	// 	new_color.g < amb.color.g * (1 - amb.ratio) && \
	// 	new_color.b < amb.color.b * (1 - amb.ratio))
	// 	new_color = add_ambient(color, amb.color, 1 - amb.ratio);
	// if (new_color.r < amb.color.r * amb.ratio)
	// 	new_color.r = color.r - amb.color.r * (1 - amb.ratio);
	// if (new_color.g < amb.color.g * amb.ratio)
	// 	new_color.g = color.g - amb.color.g * (1 - amb.ratio);
	// if (new_color.b < amb.color.b * amb.ratio)
	// 	new_color.b = color.b - amb.color.b * (1 - amb.ratio);
	return (new_color);
}

t_rgb	ft_get_ambient(t_light amb)
{
	t_rgb	color;

	color.r = amb.color.r * amb.ratio;
	color.g = amb.color.g * amb.ratio;
	color.b = amb.color.b * amb.ratio;
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
		// color = add_ambient(mrt->amblight, color);
		// linter = check_intersections(mrt, start, normalize(coor_to_light));
		linter = check_shaddow(mrt, ctr, normalize(coor_to_light), vect_norm(coor_to_light));
		if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
			color = diminish_color(ctr->color, ctr->norm, coor_to_light, mrt->amblight);
		else
			color = ft_make_rgb(0, 0, 0);//add_ambient(color, mrt->amblight.color, 1 - mrt->amblight.ratio);
	}
	if (((t_discr)(get_sph_dscr(vec_rest(mrt->cam.pos, mrt->light.pos), \
	dir, int_pow(0.2, 2)))).dscr >= 0.0)
		color = ft_make_rgb(255, 255, 255);
	return (color);
}
