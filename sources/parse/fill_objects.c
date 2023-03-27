/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:20 by ionorb            #+#    #+#             */
/*   Updated: 2023/03/24 21:32:12 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	ft_fill_sphere(t_table *table, char **line)
{
	t_sphere	sphere;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for sphere", \
		SPHERE_INSTRUCTIONS, NULL);
	sphere.center = ft_fill_pos(line[1], 0);
	sphere.dir = fill_coord(0, 0, 1);
	sphere.radius = ft_fill_size(line[2], 0) / 2;
	sphere.color = ft_fill_rgb(line[3]);
	sphere.base = get_obj_base(sphere.dir);
	sphere.base.bs_orig = sphere.center;
	sphere.option = ft_fill_options(table, sphere.color);
	return (sphere);
}

t_plane	ft_fill_plane(t_table *table, char **line)
{
	t_plane	plane;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for plane", \
		PLANE_INSTRUCTIONS, NULL);
	plane.pos = ft_fill_pos(line[1], 0);
	plane.dir = normalize(ft_fill_pos(line[2], 1));
	plane.color = ft_fill_rgb(line[3]);
	plane.base = get_obj_base(plane.dir);
	plane.base.bs_orig = plane.pos;
	plane.option = ft_fill_options(table, plane.color);
	return (plane);
}

t_cylinder	ft_fill_cylinder(t_table *table, char **line)
{
	t_cylinder	cylinder;

	if (ft_arg_count(line) != 6)
		ft_error("Wrong number of arguments for cylinder", \
		CYLINDER_INSTRUCTIONS, NULL);
	cylinder.pos = ft_fill_pos(line[1], 0);
	cylinder.dir = normalize(ft_fill_pos(line[2], 1));
	cylinder.radius = ft_fill_size(line[3], 0) / 2;
	cylinder.height = ft_fill_size(line[4], 0);
	cylinder.color = ft_fill_rgb(line[5]);
	cylinder.base = get_obj_base(cylinder.dir);
	cylinder.base.bs_orig = cylinder.pos;
	cylinder.top = vec_sum(cylinder.pos, \
	scal_vec(cylinder.height / 2, cylinder.dir));
	cylinder.bottom = vec_sum(cylinder.pos, \
	scal_vec(-cylinder.height / 2, cylinder.dir));
	cylinder.option = ft_fill_options(table, cylinder.color);
	return (cylinder);
}

t_cone	ft_fill_cone(t_table *table, char **line)
{
	t_cone	cone;

	if (ft_arg_count(line) != 6)
		ft_error("Wrong number of arguments for cone", \
		CONE_INSTRUCTIONS, NULL);
	cone.pos = ft_fill_pos(line[1], 0);
	cone.dir = normalize(ft_fill_pos(line[2], 1));
	cone.angle = ft_fill_size(line[3], 1);
	cone.height = ft_fill_size(line[4], 0);
	cone.color = ft_fill_rgb(line[5]);
	cone.base = get_obj_base(cone.dir);
	cone.base.bs_orig = cone.pos;
	cone.top = vec_sum(cone.pos, \
	scal_vec(cone.height / 2, cone.dir));
	cone.bottom = vec_sum(cone.pos, \
	scal_vec(-cone.height / 2, cone.dir));
	cone.option = ft_fill_options(table, cone.color);
	return (cone);
}

t_cam	ft_fill_cam(t_table *table, char **line)
{
	t_cam	cam;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for camera", \
		CAMERA_INSTRUCTIONS, NULL);
	cam.pos = ft_fill_pos(line[1], 0);
	cam.dir = normalize(ft_fill_pos(line[2], 1));
	cam.fov = ft_fill_size(line[3], 1);
	if (table && table->next && eval_obj(table->next->line[0]) == OPTION)
		ft_error("Cameras have no available options", NULL, NULL);
	return (cam);
}

t_light	ft_fill_light(t_table *table, char **line, int amb)
{
	t_light		light;
	int			i;

	i = 1;
	if (ft_arg_count(line) != (4 - amb))
		ft_error("Wrong number of arguments for light", \
		LIGHT_INSTRUCTIONS, NULL);
	if (!amb)
		light.pos = ft_fill_pos(line[i++], 0);
	light.ratio = ft_fill_ratio(line[i++]);
	light.color = ft_fill_rgb(line[i++]);
	light.type = amb;
	if (table && table->next && eval_obj(table->next->line[0]) == OPTION)
		ft_error("Lights have no available options", NULL, NULL);
	return (light);
}
