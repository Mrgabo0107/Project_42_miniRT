/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_global_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:36:59 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 23:24:19 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_amblight	ft_fill_ambient(char *line[7])
{
	t_amblight	amblight;

	// amblight = (t_amblight *)ft_malloc(sizeof(t_amblight));
	if (ft_arg_count(line) != 3)
		ft_error("Wrong number of arguments for ambient light", NULL);
	// ft_check_chars(line + 1, "0123456789.-,");
	amblight.ratio = ft_fill_ratio(line[1]);
	amblight.color = ft_fill_rgb(line[2]);
	return (amblight);
}

t_cam	ft_fill_cam(char *line[7])
{
	t_cam	cam;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for camera", NULL);
	// ft_check_chars(line + 1, "0123456789.-,");
	cam.pos = ft_fill_pos(line[1]);
	cam.dir = ft_fill_dir(line[2]);
	cam.fov = ft_fill_fov(line[3]);
	return (cam);
}

t_light	ft_fill_light(char *line[7])
{
	t_light	light;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for light", NULL);
	// ft_check_chars(line + 1, "0123456789.-,");
	light.pos = ft_fill_pos(line[1]);
	light.ratio = ft_fill_ratio(line[2]);
	light.color = ft_fill_rgb(line[3]);
	return (light);
}
