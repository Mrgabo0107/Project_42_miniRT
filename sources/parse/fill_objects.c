/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:20 by ionorb            #+#    #+#             */
/*   Updated: 2023/04/04 19:20:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	ft_fill_sphere(char *line[7])
{
	t_sphere	sphere;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for sphere", \
		SPHERE_INSTRUCTIONS, NULL);
	sphere.center = ft_fill_pos(line[1], 0);
	sphere.radius = ft_fill_size(line[2], 0) / 2;
	sphere.color = ft_fill_rgb(line[3]);
	return (sphere);
}

t_plane	ft_fill_plane(char *line[7])
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
	return (plane);
}

t_cylinder	ft_fill_cylinder(char *line[7])
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
	return (cylinder);
}

t_cam	ft_fill_cam(char *line[7])
{
	t_cam	cam;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for camera", \
		CAMERA_INSTRUCTIONS, NULL);
	cam.pos = ft_fill_pos(line[1], 0);
	cam.dir = normalize(ft_fill_pos(line[2], 1));
	cam.fov = ft_fill_size(line[3], 1);
	return (cam);
}

t_light	ft_fill_light(char *line[7], int amb)
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
	return (light);
}
