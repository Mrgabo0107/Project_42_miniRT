/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 01:29:54 by yoel              #+#    #+#             */
/*   Updated: 2023/04/05 02:07:47 by gamoreno         ###   ########.fr       */
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

t_rgb	get_reflection(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	t_vec	refl_dir;
	t_vec	point;
	t_inter	refl_inter;
	t_rgb	color;

	mrt->bounce++;
	refl_dir = vec_sum(dir, scal_vec(-2 * dot_prod(dir, ctr->norm), \
	ctr->norm));
	point = vec_sum(ctr->inter_coor, scal_vec(0.0000001, ctr->norm));
	refl_inter = check_intersections(mrt, point, refl_dir);
	refl_inter.norm = get_normal_at_point(mrt, refl_inter);
	color = get_object_color(mrt, &refl_inter, refl_dir, ft_make_rgb(0, 0, 0));
	return (color);
}

t_rgb	get_diffuse(t_inter *ctr, t_vec to_light, t_light light)
{
	double	angle;
	t_rgb	ratio;
	t_rgb	color;

	angle = dot_prod(normalize(ctr->norm), normalize(to_light));
	if (angle < 0)
		angle = 0;
	// printf("angle %f\n", angle);
	ratio = ft_make_rgb_ratio(ctr->color);
	color.r = light.color.r * light.ratio * ratio.r * angle;
	color.g = light.color.g * light.ratio * ratio.g * angle;
	color.b = light.color.b * light.ratio * ratio.b * angle;
	return (color);
}

t_rgb	get_specular(t_inter *ctr, t_vec pos, t_vec to_light, t_light light)
{
	double	ratio;
	t_rgb	color;
	t_vec	h;
	int		exponent;
	double	intensity;

	intensity = ctr->option.specular[0];
	exponent = (int)ctr->option.specular[1];
	h = normalize(scal_vec(1 / vect_norm(normalize(vec_sum(normalize(to_light), \
	normalize(vec_rest(pos, ctr->inter_coor))))), \
	normalize(vec_sum(normalize(to_light), \
	normalize(vec_rest(pos, ctr->inter_coor))))));
	ratio = \
	intensity * int_pow(dot_prod(normalize(ctr->norm), h), exponent * 10);
	color.r = light.color.r * light.ratio * ratio;
	color.g = light.color.g * light.ratio * ratio;
	color.b = light.color.b * light.ratio * ratio;
	return (color);
}
