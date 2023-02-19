/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/19 13:57:36 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_count_objs(t_table *table)
{
	int	count[3];

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	while (table)
	{
		if (eval_obj(table->line[0]) == AMBIENT)
			count[0]++;
		else if (eval_obj(table->line[0]) == CAMERA)
			count[1]++;
		else if (eval_obj(table->line[0]) == LIGHT)
			count[2]++;
		else if (eval_obj(table->line[0]) == -1)
			return (ft_error(INVALID_OBJECT, table->line[0], EXIT_ERROR), 1);
		table = table->next;
	}
	if (count[0] > 1 || count[1] > 1 || count[2] > 1)
		return (ft_error(TOO_MANY_CAPITALS, NULL, EXIT_ERROR), 1);
	if (count[0] == 0 || count[1] == 0 || count[2] == 0)
		return (ft_error(MISSING_CAPITALS, NULL, EXIT_ERROR), 1);
	return (0);
}

int	ft_fill_objs(t_mrt *mrt, t_table *table)
{
	t_lst	*scene;
	// t_obj	*obj;

	scene = NULL;
	// obj = scene->obj;
	while (table)
	{
		if (eval_obj(table->line[0]) == AMBIENT)
			ft_lstadd_new(scene, ft_fill_ambient(table->line), AMBIENT);
		else if (eval_obj(table->line[0]) == CAMERA)
			ft_lstadd_new(scene, ft_fill_cam(table->line), CAMERA);
		else if (eval_obj(table->line[0]) == LIGHT)
			ft_lstadd_new(scene, ft_fill_light(table->line), LIGHT);
		else if (eval_obj(table->line[0]) == SPHERE)
			ft_lstadd_new(scene, ft_fill_sphere(table->line), SPHERE);
		else if (eval_obj(table->line[0]) == PLANE)
			ft_lstadd_new(scene, ft_fill_plane(table->line), PLANE);
		else if (eval_obj(table->line[0]) == CYLINDER)
			ft_lstadd_new(scene, ft_fill_cylinder(table->line), CYLINDER);
		table = table->next;
	}
	scene = mrt->scene;
	return (0);
}

int	ft_parse(t_mrt *mrt, char *file)
{
	t_table	*table;
	int		i;

	table = ft_fill_table(file);
	ft_count_objs(table);
	ft_fill_objs(mrt, table);
	while (table)
	{
		i = 0;
		while (i < 7) //table->line[i])
			printf("[%s] ", table->line[i++]);
		printf("\n");
		table = table->next;
	}
	return (0);
}
