/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/02 21:09:46 by ana              ###   ########.fr       */
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

t_rgb	diminish_color(t_rgb color, t_vec vec1, t_vec vec2, double ambient)
{
	float	angle;
	float	ratio;

	angle = get_angle_between(vec1, vec2);
	if (angle > PI / 2)
		angle = PI / 2;
	ratio = angle / (PI / 2);// + (1 - ambient);
	color.r -= color.r * ratio;
	color.g -= color.g * ratio;
	color.b -= color.b * ratio;
	return (color);
}

t_vec	vec_mult(t_vec vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	return (vec);
}

t_inter	check_shaddow(t_mrt *mrt, t_vec point, t_vec dir, double len)
{
	t_inter	ret;

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

// uint	add_ambient(t_light amb, uint color)
// {
// 	uint	r;
// 	uint	g;
// 	uint	b;

// 	r = (color >> 16) & 0xFF;
// 	g = (color >> 8) & 0xFF;
// 	b = color & 0xFF;
// 	r += amb.ratio *;
// 	g += amb.ratio;
// 	b += amb.ratio;
// 	if (r > 255)
// 		r = 255;
// 	if (g > 255)
// 		g = 255;
// 	if (b > 255)
// 		b = 255;
// 	if (r > 255 || g < 0 || b < 0)
// 		print255("r: %d, g: %d, b: %d\n", r, g, b);
// 	return ((r << 16) | (g << 8) | b);
// }

t_rgb	get_color(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	t_rgb	color;
	t_vec	coor_to_light;
	t_inter	linter;
	t_vec	start;
	// t_discr	discr;

	color = ft_make_rgb(0, 0, 0);
	if (ctr->dist != -1)
	{
		coor_to_light = vec_rest(mrt->light.pos, ctr->inter_coor);
		if (ctr->type == SPHERE)
			color = mrt->sphere[ctr->index].color;
		if (ctr->type == CYLINDER)
			color = mrt->cylinder[ctr->index].color;
		if (ctr->type == PLANE)
			color = mrt->plane[ctr->index].color;
		// color = add_ambient(mrt->amblight, color);
		start = vec_sum(ctr->inter_coor, vec_mult(ctr->norm, 0.0000001));
		// linter = check_intersections(mrt, start, normalize(coor_to_light));
		linter = check_shaddow(mrt, start, normalize(coor_to_light), vect_norm(coor_to_light));
		if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
			color = diminish_color(color, ctr->norm, coor_to_light, \
			mrt->amblight.ratio);
		else
			color = ft_make_rgb(0, 0, 0);
			// color = color = diminish_color(color, ctr->norm, ctr->norm, \
			// mrt->amblight.ratio);
	}
	if (((t_discr)(get_sph_dscr(vec_rest(mrt->cam.pos, mrt->light.pos), \
	dir, int_pow(0.2, 2)))).dscr >= 0.0)
		color = ft_make_rgb(255, 255, 255);
	return (color);
}
