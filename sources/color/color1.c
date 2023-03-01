/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/02 00:34:45 by ana              ###   ########.fr       */
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

uint	diminish_color(uint color, t_vec vec1, t_vec vec2, double ambient)
{
	uint	r;
	uint	g;
	uint	b;
	float	angle;
	float	ratio;

	angle = get_angle_between(vec1, vec2);
	if (angle > PI / 2)
		angle = PI / 2;
	ratio = angle / (PI / 2);// + (1 - ambient);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	// if (ambient != -1)
	// {
	// 	r -= r * (1 - ambient);
	// 	g -= g * (1 - ambient);
	// 	b -= b * (1 - ambient);
	// }
	// else
	// {
		r -= r * ratio;
		g -= g * ratio;
		b -= b * ratio;
	// }
	// printf("2: r: %d, g: %d, b: %d\n", r, g, b);
	return ((r << 16) | (g << 8) | b);
}

t_vec	vec_mult(t_vec vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	vec.z *= mult;
	return (vec);
}

uint	get_color(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	int		color;
	t_vec	coor_to_light;
	t_inter	linter;
	t_vec	start;
	// t_discr	discr;

	color = 0x00000;
	if (ctr->dist != -1)
	{
		coor_to_light = vec_rest(mrt->light.pos, ctr->inter_coor);
		if (ctr->type == SPHERE)
			color = mrt->sphere[ctr->index].color;
		if (ctr->type == CYLINDER)
			color = mrt->cylinder[ctr->index].color;
		if (ctr->type == PLANE)
			color = mrt->plane[ctr->index].color;
		start = vec_sum(ctr->inter_coor, vec_mult(ctr->norm, 0.0000001));
		linter = check_intersections(mrt, start, normalize(coor_to_light));
		if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
			color = diminish_color(color, ctr->norm, coor_to_light, \
			mrt->amblight.ratio);
		else
			color = 0x000000;
			// color = color = diminish_color(color, ctr->norm, ctr->norm, \
			// mrt->amblight.ratio);
	}
	if (((t_discr)(get_sph_dscr(vec_rest(mrt->cam.pos, mrt->light.pos), \
	dir, int_pow(0.2, 2)))).dscr >= 0.0)
		color = 0xFFFFFF;
	return (color);
}
