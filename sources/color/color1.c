/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/01 21:33:12 by ana              ###   ########.fr       */
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

uint	diminish_color(uint color, t_vec vec1, t_vec vec2)
{
	uint	r;
	uint	g;
	uint	b;
	float	angle;

	angle = get_angle_between(vec1, vec2);
	if (angle > PI / 2)
		angle = PI / 2;//PI - angle;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	// printf("angle: %f, ratio %f\n", angle, angle / (PI));
	// printf("1: r: %d, g: %d, b: %d\n", r, g, b);
	// if (angle > PI - 0.1)
	// 	printf("angle: %f, ratio %f\n", angle, angle / (PI));
	r -= r * angle / (PI / 2);
	g -= g * angle / (PI / 2);
	b -= b * angle / (PI / 2);
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

uint	get_color(t_mrt *mrt, t_inter *ctr)
{
	int		color;
	t_vec	light_direction;
	t_inter	linter;
	t_vec	start;

	color = 0x00000;
	if (ctr->dist != -1)
	{
		light_direction = vec_rest(mrt->light.pos, ctr->inter_coor);
		if (ctr->type == SPHERE)
			color = mrt->sphere[ctr->index].color;
		if (ctr->type == CYLINDER)
			color = mrt->cylinder[ctr->index].color;
		if (ctr->type == PLANE)
			color = mrt->plane[ctr->index].color;
		start = vec_sum(ctr->inter_coor, vec_mult(ctr->norm, 0.0000001));
		linter = check_intersections(mrt, start, light_direction);
		if (linter.dist < 0 || linter.dist > vect_norm(light_direction))
			color = diminish_color(color, ctr->norm, light_direction);
		else
			color = 0x000000;
	}
	// if (color > 0)
		// printf("color: %d\n", color);
	return (color);
}
