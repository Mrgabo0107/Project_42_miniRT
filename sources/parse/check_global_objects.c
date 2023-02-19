/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_global_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:36:59 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 13:39:14 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_amblight	*ft_fill_ambient(char *line[7])
{
	t_amblight	*amblight;

	(void)line;
	amblight = (t_amblight *)ft_malloc(sizeof(t_amblight));
	return (amblight);
}

t_cam		*ft_fill_cam(char *line[7])
{
	t_cam	*cam;

	(void)line;
	cam = (t_cam *)ft_malloc(sizeof(t_cam));
	return (cam);
}

t_light		*ft_fill_light(char *line[7])
{
	t_light	*light;

	(void)line;
	light = (t_light *)ft_malloc(sizeof(t_light));
	return (light);
}
