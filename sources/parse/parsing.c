/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/05 03:08:40 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_capitals(int a, int c, int l)
{
	if (a > 1)
		ft_error(TOO_MANY_AMBIENTS, AMBIENT_INSTRUCTIONS, NULL);
	if (c > 1)
		ft_error(TOO_MANY_CAMERAS, CAMERA_INSTRUCTIONS, NULL);
	if (a == 0)
		ft_error(MISSING_AMBIENT, AMBIENT_INSTRUCTIONS, NULL);
	if (c == 0)
		ft_error(MISSING_CAMERA, CAMERA_INSTRUCTIONS, NULL);
	if (l == 0)
		ft_error(MISSING_LIGHT, LIGHT_INSTRUCTIONS, NULL);
}

int	*ft_count_objs(t_table *table, int *count)
{
	while (table)
	{
		if (eval_obj(table->line[0]) == AMBIENT)
			count[AMBIENT]++;
		else if (eval_obj(table->line[0]) == CAMERA)
			count[CAMERA]++;
		else if (eval_obj(table->line[0]) == LIGHT)
			count[LIGHT]++;
		else if (eval_obj(table->line[0]) == PLANE)
			count[PLANE]++;
		else if (eval_obj(table->line[0]) == SPHERE)
			count[SPHERE]++;
		else if (eval_obj(table->line[0]) == CYLINDER)
			count[CYLINDER]++;
		else if (eval_obj(table->line[0]) == CONE)
			count[CONE]++;
		else if (eval_obj(table->line[0]) == TRIANGLE)
			count[TRIANGLE]++;
		else if (eval_obj(table->line[0]) == -1)
			ft_error(INVALID_OBJECT, table->line[0], OBJECT_INSTRUCTIONS);
		table = table->next;
	}
	return (ft_check_capitals(count[AMBIENT], count[CAMERA],
			count[LIGHT]), count);
}

void	ft_fill_capitals(t_mrt *mrt, t_table *table, char **line, int type)
{
	if (type == AMBIENT)
		mrt->amblight = ft_fill_light(table, line, 1);
	else if (type == CAMERA)
		mrt->cam = ft_fill_cam(table, line);
}

void	ft_fill_objs(t_mrt *mrt, t_table *table, int *count)
{
	int	type;

	ft_allocate_objs(mrt, count);
	while (table)
	{
		type = eval_obj(table->line[0]);
		if (type == AMBIENT || type == CAMERA)
			ft_fill_capitals(mrt, table, table->line, type);
		else if (eval_obj(table->line[0]) == LIGHT)
			mrt->light[--count[LIGHT]] = ft_fill_light(table, table->line, 0);
		else if (eval_obj(table->line[0]) == SPHERE)
			mrt->sphere[--count[SPHERE]] = ft_fill_sphere(table, table->line);
		else if (eval_obj(table->line[0]) == PLANE)
			mrt->plane[--count[PLANE]] = ft_fill_plane(table, table->line);
		else if (eval_obj(table->line[0]) == CYLINDER)
			mrt->cylinder[--count[CYLINDER]] = \
			ft_fill_cylinder(table, table->line);
		else if (eval_obj(table->line[0]) == CONE)
			mrt->cone[--count[CONE]] = ft_fill_cone(table, table->line);
		else if (eval_obj(table->line[0]) == TRIANGLE)
			mrt->triangle[--count[TRIANGLE]] \
			= ft_fill_triangle(table, table->line);
		table = table->next;
	}
	ft_free(count);
}

int	ft_parse(t_mrt *mrt)
{
	int		fd;
	t_table	*table;

	fd = open(mrt->scene_path, O_RDONLY);
	if (fd < 0)
		ft_error(FILE_ERROR, mrt->scene_path, strerror(errno));
	ft_memory(&fd, SAVE_FD);
	if (!valid_rt_file(mrt->scene_path, fd))
		ft_error(INVALID_FILE, mrt->scene_path, FILE_INSTRUCTIONS);
	table = ft_fill_table(fd, mrt->num_objs);
	ft_close_fd(&fd);
	mrt->obj_count = ft_count_objs(table, mrt->obj_count);
	ft_fill_objs(mrt, table, int_arrcpy(mrt->obj_count, mrt->num_objs));
	ft_free_table(table);
	return (0);
}
