/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/15 16:58:50 by yridgway         ###   ########.fr       */
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

	refl_dir = vec_sum(dir, scal_vec(-2 * dot_prod(dir, ctr->norm), \
	ctr->norm));
	point = vec_sum(ctr->inter_coor, scal_vec(0.0000001, ctr->norm));
	refl_inter = check_intersections(mrt, point, refl_dir);
	refl_inter.norm = get_normal_at_point(mrt, refl_inter);
	color = get_color(mrt, &refl_inter, refl_dir);
	return (color);
}

t_rgb	get_object_color(t_mrt *mrt, t_inter *ctr, t_vec dir, t_rgb color)
{
	t_vec	coor_to_light;
	t_inter	linter;
	t_vec	h;
	int		i;

	i = -1;
	while (++i < mrt->obj_count[LIGHT])
	{
		coor_to_light = vec_rest(mrt->light[i].pos, ctr->inter_coor);
		linter = check_shaddow(mrt, ctr, normalize(coor_to_light), \
		vect_norm(coor_to_light));
		// if (ctr->type == PLANE)
		// 	color = get_reflection(mrt, ctr, dir);
		if ((linter.dist < 0 || linter.dist > vect_norm(coor_to_light)))
		{
			h = scal_vec(1 / vect_norm(vec_sum(coor_to_light, \
			vec_rest(mrt->cam.pos, ctr->inter_coor))), \
			vec_sum(coor_to_light, vec_rest(mrt->cam.pos, \
			ctr->inter_coor)));
			color = add_diffuse(ctr, color, coor_to_light, mrt->light[i]);
			color = add_specular(ctr, color, h, mrt->light[i]);
		}
	}
	color = add_ambient(color, ctr->color, mrt->amblight);
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
