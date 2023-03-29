/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_capitals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:01:24 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/29 23:01:56 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	ft_fill_cam(t_table *table, char **line)
{
	t_cam	cam;

	if (ft_arg_count(line) != 4)
		ft_error("Wrong number of arguments for camera",
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
	t_light	light;
	int		i;

	i = 1;
	if (ft_arg_count(line) != (4 - amb))
		ft_error("Wrong number of arguments for light",
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
