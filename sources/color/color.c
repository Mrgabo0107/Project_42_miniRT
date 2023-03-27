/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/28 01:47:38 by yoel             ###   ########.fr       */
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

t_rgb	get_radiance(t_mrt *mrt, t_inter *ctr, t_vec dir, t_light light)
{
	t_vec	to_light;
	t_inter	linter;
	t_rgb	reflection;
	t_rgb	diffuse;
	t_rgb	specular;

	reflection = ft_make_rgb(0, 0, 0);
	diffuse = ft_make_rgb(0, 0, 0);
	specular = ft_make_rgb(0, 0, 0);
	to_light = vec_rest(light.pos, ctr->inter_coor);
	linter = check_shaddow(mrt, ctr, normalize(to_light), vect_norm(to_light));
	if ((linter.dist < 0 || linter.dist > vect_norm(to_light)))
	{
		if (ctr->option.mirror < 1)
			diffuse = get_diffuse(ctr, to_light, light);
		if (ctr->option.specular > 0)
			specular = get_specular(ctr, mrt->cam.pos, to_light, light);
	}
	reflection = mult_color(reflection, ctr->option.mirror);
	diffuse = mult_color(diffuse, 1 - ctr->option.mirror);
	specular = mult_color(specular, 1 - ctr->option.mirror);
	return (add_color(add_color(reflection, diffuse), specular));
}

t_rgb	get_object_color(t_mrt *mrt, t_inter *ctr, t_vec dir, t_rgb color)
{
	int		i;
	t_rgb	reflection;

	i = -1;
	while (++i < mrt->obj_count[LIGHT])
		color = add_color(color, \
		get_radiance(mrt, ctr, dir, mrt->light[i]));
	if (ctr->option.mirror > 0 && mrt->bounce < 40)
		reflection = get_reflection(mrt, ctr, dir);
	color = add_color(color, reflection);
	return (add_color(color, get_ambient(ctr->color, mrt->amblight, 1)));
}

t_rgb	get_color(t_mrt *mrt, t_inter *ctr, t_vec dir)
{
	t_rgb	color;

	color = ft_make_rgb(0, 0, 0);
	if (ctr->dist != -1)
		color = get_object_color(mrt, ctr, dir, color);
	color = show_light_sources(mrt, color, dir);
	return (color);
}
