/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/19 00:51:07 by ionorb           ###   ########.fr       */
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
			return (printf("Error\n"), ft_quit(INVALID_OBJECT, EXIT_ERROR), 1);
		table = table->next;
	}
	if (count[0] > 1 || count[1] > 1 || count[2] > 1)
		return (printf("Error\n"), ft_quit(TOO_MANY_CAPITALS, EXIT_ERROR), 1);
	if (count[0] == 0 || count[1] == 0 || count[2] == 0)
		return (printf("Error\n"), ft_quit(MISSING_CAPITALS, EXIT_ERROR), 1);
	return (0);
}

int	ft_fill_objs(t_mrt *mrt, t_table *table)
{
	int	i;

	i = 0;
	while (table)
	{
		if (eval_obj(table->line[0]) == AMBIENT)
			mrt->ambient = ft_fill_ambient(table->line);
		else if (eval_obj(table->line[0]) == CAMERA)
			mrt->camera = ft_fill_camera(table->line);
		else if (eval_obj(table->line[0]) == LIGHT)
			mrt->light = ft_fill_light(table->line);
		else if (eval_obj(table->line[0]) == SPHERE)
			mrt->sphere = ft_fill_sphere(table->line);
		else if (eval_obj(table->line[0]) == PLANE)
			mrt->plane = ft_fill_plane(table->line);
		else if (eval_obj(table->line[0]) == CYLINDER)
			mrt->cylinder = ft_fill_cylinder(table->line);
		table = table->next;
	}
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
