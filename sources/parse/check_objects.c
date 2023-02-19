/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:20 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 13:39:05 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*ft_fill_sphere(char *line[7])
{
	t_sphere	*sphere;

	(void)line;
	sphere = (t_sphere *)ft_malloc(sizeof(t_sphere));
	return (sphere);
}

t_plane	*ft_fill_plane(char *line[7])
{
	t_plane	*plane;

	(void)line;
	plane = (t_plane *)ft_malloc(sizeof(t_plane));
	return (plane);
}

t_cylinder	*ft_fill_cylinder(char *line[7])
{
	t_cylinder	*cylinder;

	(void)line;
	cylinder = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	return (cylinder);
}
