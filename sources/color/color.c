/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/19 22:55:14 by yoel             ###   ########.fr       */
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
	color = get_color(mrt, &refl_inter, refl_dir);
	return (color);
}

t_rgb	get_radiance(t_mrt *mrt, t_inter *ctr, t_vec dir, t_light light)
{
	t_rgb	color;
	t_vec	coor_to_light;
	t_inter	linter;
	t_vec	h;

	color = ft_make_rgb(0, 0, 0);
	coor_to_light = vec_rest(light.pos, ctr->inter_coor);
	linter = check_shaddow(mrt, ctr, normalize(coor_to_light), \
	vect_norm(coor_to_light));
	if (ctr->option.mirror > 0 && mrt->bounce < 100)
			color = mult_color(get_reflection(mrt, ctr, dir), \
			ctr->option.mirror);
	if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
	{
		h = scal_vec(1 / vect_norm(vec_sum(coor_to_light, \
		vec_rest(mrt->cam.pos, ctr->inter_coor))), \
		vec_sum(coor_to_light, vec_rest(mrt->cam.pos, \
		ctr->inter_coor)));
		// color = mult_color(color, 1 - ctr->option.mirror);
		color = add_diffuse(ctr, color, coor_to_light, light);
		color = add_specular(ctr, color, h, light);
	}
	return (color);
}

t_rgb	get_object_color(t_mrt *mrt, t_inter *ctr, t_vec dir, t_rgb color)
{
	int		i;

	i = -1;
	while (++i < mrt->obj_count[LIGHT])
		color = get_radiance(mrt, ctr, dir, mrt->light[i]);
	color = add_ambient(color, ctr->color, mrt->amblight, 1);
	return (color);
}

t_rgb	get_color(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	t_rgb	color;

	color = ft_make_rgb(0, 0, 0);
	if (ctr->dist != -1)
		color = get_object_color(mrt, ctr, dir, color);
	color = show_light_sources(mrt, color, dir);
	color = normalize_color(color);
	return (color);
}
