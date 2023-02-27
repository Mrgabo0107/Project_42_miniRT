/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:20 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/27 17:38:02 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	ft_fill_sphere(char *line[7])
{
	t_sphere	sphere;

	printf("filling sphere\n");
	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for sphere", NULL);
	sphere.center = ft_fill_pos(line[1], 0);
	sphere.radius = ft_fill_size(line[2], 0) / 2;
	sphere.color = ft_fill_rgb(line[3]);
	return (sphere);
}

t_plane	ft_fill_plane(char *line[7])
{
	t_plane	plane;

	printf("filling plane\n");
	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for plane", NULL);
	plane.pos = ft_fill_pos(line[1], 0);
	plane.dir = normalize(ft_fill_pos(line[2], 1));
	plane.color = ft_fill_rgb(line[3]);
	return (plane);
}

t_cylinder	ft_fill_cylinder(char *line[7])
{
	t_cylinder	cylinder;

	printf("filling cylinder\n");
	if (ft_arg_count(line) != 6)
		ft_error("Wrong number of arguments for cylinder", NULL);
	cylinder.pos = ft_fill_pos(line[1], 0);
	cylinder.dir = normalize(ft_fill_pos(line[2], 1));
	cylinder.radius = ft_fill_size(line[3], 0) / 2;
	cylinder.height = ft_fill_size(line[4], 0);
	cylinder.color = ft_fill_rgb(line[5]);
	cylinder.base = get_cyl_base(cylinder.dir);
	cylinder.top = vec_sum(cylinder.pos, \
	scal_vec(cylinder.height / 2, cylinder.dir));
	cylinder.bottom = vec_sum(cylinder.pos, \
	scal_vec(-cylinder.height / 2, cylinder.dir));
	return (cylinder);
}

t_cam	ft_fill_cam(char *line[7])
{
	t_cam	cam;

	printf("filling camera\n");
	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for camera", NULL);
	cam.pos = ft_fill_pos(line[1], 0);
	cam.dir = normalize(ft_fill_pos(line[2], 1));
	cam.fov = ft_fill_size(line[3], 1);
	printf("Center: %f, %f, %f\n", cam.pos.x, cam.pos.y, cam.pos.z);
	return (cam);
}

t_light	ft_fill_light(char *line[7], int amb)
{
	t_light		light;
	int			i;

	printf("filling light %s\n", line[0]);
	i = 1;
	if (ft_arg_count(line) != (4 - amb))
		ft_error("Wrong number of arguments for light", NULL);
	if (!amb)
		light.pos = ft_fill_pos(line[i++], 0);
	light.ratio = ft_fill_ratio(line[i++]);
	light.color = ft_fill_rgb(line[i++]);
	light.type = amb;
	return (light);
}
