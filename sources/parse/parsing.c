/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/22 21:19:44 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_capitals(int a, int c, int l)
{
	if (a > 1 || c > 1 || l > 1)
		ft_error(TOO_MANY_CAPITALS, NULL);
	if (a == 0 || c == 0 || l == 0)
		ft_error(MISSING_CAPITALS, NULL);
}

int	*ft_count_objs(t_table *table, int obj_count[6])
{
	int	i;

	i = 0;
	while (i < 6)
		obj_count[i++] = 0;
	while (table)
	{
		if (eval_obj(table->line[0]) == AMBIENT)
			(obj_count[AMBIENT])++;
		else if (eval_obj(table->line[0]) == CAMERA)
			(obj_count[CAMERA])++;
		else if (eval_obj(table->line[0]) == LIGHT)
			(obj_count[LIGHT])++;
		else if (eval_obj(table->line[0]) == PLANE)
			(obj_count[PLANE])++;
		else if (eval_obj(table->line[0]) == SPHERE)
			(obj_count[SPHERE])++;
		else if (eval_obj(table->line[0]) == CYLINDER)
			(obj_count[CYLINDER])++;
		else if (eval_obj(table->line[0]) == -1)
			ft_error(INVALID_OBJECT, table->line[0]);
		table = table->next;
	}
	return (ft_check_capitals(obj_count[AMBIENT], obj_count[CAMERA],
			obj_count[LIGHT]), obj_count);
}

void	ft_fill_capitals(t_mrt *mrt, char **line, int type)
{
	if (type == AMBIENT)
		mrt->amblight = ft_fill_light(line, 1);
	else if (type == CAMERA)
		mrt->cam = ft_fill_cam(line);
	else if (type == LIGHT)
		mrt->light = ft_fill_light(line, 0);
}

void	ft_fill_objs(t_mrt *mrt, t_table *table, int count[6])
{
	int	type;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	mrt->sphere = ft_malloc(sizeof(t_sphere) * count[SPHERE]);
	mrt->plane = ft_malloc(sizeof(t_plane) * count[PLANE]);
	mrt->cylinder = ft_malloc(sizeof(t_cylinder) * count[CYLINDER]);
	while (table)
	{
		type = eval_obj(table->line[0]);
		if (type >= AMBIENT && type <= LIGHT)
			ft_fill_capitals(mrt, table->line, type);
		else if (eval_obj(table->line[0]) == SPHERE)
			mrt->sphere[i++] = ft_fill_sphere(table->line);
		else if (eval_obj(table->line[0]) == PLANE)
			mrt->plane[j++] = ft_fill_plane(table->line);
		else if (eval_obj(table->line[0]) == CYLINDER)
			mrt->cylinder[k++] = ft_fill_cylinder(table->line);
		table = table->next;
	}
}

int	ft_parse(t_mrt *mrt, char *file)
{
	t_table	*table;
	int		i;

	table = ft_fill_table(file);
	ft_count_objs(table, mrt->obj_count);
	ft_fill_objs(mrt, table, mrt->obj_count);
	while (table)
	{
		i = 0;
		while (i < 7)
			ft_printf("[%s] ", table->line[i++]);
		ft_printf("\n");
		table = table->next;
	}
	return (0);
}
