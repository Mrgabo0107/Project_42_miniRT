/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:20 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 23:08:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	ft_fill_sphere(char *line[7])
{
	t_sphere	sphere;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for sphere", NULL);
	sphere.center = ft_fill_pos(line[1]);
	sphere.radius = ft_fill_size(line[2]) / 2;
	sphere.color = ft_fill_rgb(line[3]);
	return (sphere);
}

t_plane	ft_fill_plane(char *line[7])
{
	t_plane	plane;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for plane", NULL);
	plane.pos = ft_fill_pos(line[1]);
	plane.dir = ft_fill_dir(line[2]);
	plane.color = ft_fill_rgb(line[3]);
	return (plane);
}

t_cylinder	ft_fill_cylinder(char *line[7])
{
	t_cylinder	cylinder;

	if (ft_arg_count(line) != 6)
		ft_error("Wrong number of arguments for cylinder", NULL);
	cylinder.pos = ft_fill_pos(line[1]);
	cylinder.dir = ft_fill_dir(line[2]);
	cylinder.diameter = ft_fill_size(line[3]);
	cylinder.height = ft_fill_size(line[4]);
	cylinder.color = ft_fill_rgb(line[5]);
	return (cylinder);
}
