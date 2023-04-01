/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:47:46 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/01 20:17:39 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal_at_point(t_mrt *mrt, t_inter inter)
{
	t_vec	ret;

	ret = fill_coord(0, 0, 0);
	if (inter.type == PLANE)
		ret = get_normal_plane(mrt, inter);
	else if (inter.type == SPHERE)
		ret = get_normal_sphere(mrt, inter);
	else if (inter.type == CYLINDER)
		ret = get_normal_cylinder(mrt, inter);
	else if (inter.type == TRIANGLE)
		ret = get_normal_triangle(mrt, inter);
	return (ret);
}

t_rgb	get_radiance(t_mrt *mrt, t_inter *ctr, t_light light)
{
	t_vec	to_light;
	t_inter	linter;
	t_rgb	diffuse;
	t_rgb	specular;

	diffuse = ft_make_rgb(0, 0, 0);
	specular = ft_make_rgb(0, 0, 0);
	to_light = vec_rest(light.pos, ctr->inter_coor);
	linter = check_shaddow(mrt, ctr, normalize(to_light), vect_norm(to_light));
	if ((linter.dist < 0 || linter.dist > vect_norm(to_light)))
	{
		if (ctr->option.mirror < 1.0)
			diffuse = get_diffuse(ctr, to_light, light);
		if (ctr->option.specular[0] > 0)
			specular = get_specular(ctr, mrt->cam.pos, to_light, light);
	}
	diffuse = mult_color(diffuse, 1 - ctr->option.mirror);
	specular = mult_color(specular, 1 - ctr->option.mirror);
	return (add_color(diffuse, specular));
}

t_rgb	get_object_color(t_mrt *mrt, t_inter *ctr, t_vec dir, t_rgb color)
{
	int		i;
	t_rgb	reflection;

	i = -1;
	if (ctr->dist == -1)
		return (ft_make_rgb(0, 0, 0));
	reflection = ft_make_rgb(0, 0, 0);
	while (++i < mrt->obj_count[LIGHT])
		color = add_color(color, \
		get_radiance(mrt, ctr, mrt->light[i]));
	if (ctr->option.mirror > 0 && mrt->bounce < 40)
		reflection = mult_color(get_reflection(mrt, ctr, dir), \
		ctr->option.mirror);
	color = add_color(color, reflection);
	return (add_color(color, get_ambient(ctr->color, mrt->amblight, 1)));
}

int	get_pixel_color(t_mrt *mrt, int x, int y)
{
	t_inter	inter;
	t_rgb	color;
	t_vec	dir;

	dir = normalize(vec_rest(screen_pxl_by_indx(mrt, \
	&mrt->cam, x + 1, y + 1), mrt->cam.pos));
	color = ft_make_rgb(0, 0, 0);
	inter = check_intersections(mrt, mrt->cam.pos, dir);
	if (inter.dist != -1)
	{
		inter.norm = get_normal_at_point(mrt, inter);
		color = get_object_color(mrt, &inter, dir, color);
		color = chosen_obj(mrt, x, y, color);
	}
	mrt->bounce = 0;
	color = normalize_color(color);
	color = show_light_sources(mrt, color, dir);
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}
