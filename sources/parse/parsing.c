/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/12 22:13:02 by yoel             ###   ########.fr       */
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
			ft_error(INVALID_OBJECT, table->line[0], OBJECT_INSTRUCTIONS);
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
}

void	ft_fill_objs(t_mrt *mrt, t_table *table, int count[6])
{
	int	type;

	mrt->light = ft_malloc(sizeof(t_light) * count[LIGHT]);
	mrt->sphere = ft_malloc(sizeof(t_sphere) * count[SPHERE]);
	mrt->plane = ft_malloc(sizeof(t_plane) * count[PLANE]);
	mrt->cylinder = ft_malloc(sizeof(t_cylinder) * count[CYLINDER]);
	while (table)
	{
		type = eval_obj(table->line[0]);
		if (type == AMBIENT || type == CAMERA)
			ft_fill_capitals(mrt, table->line, type);
		else if (eval_obj(table->line[0]) == LIGHT)
			mrt->light[--count[LIGHT]] = ft_fill_light(table->line, 0);
		else if (eval_obj(table->line[0]) == SPHERE)
			mrt->sphere[--count[SPHERE]] = ft_fill_sphere(table->line);
		else if (eval_obj(table->line[0]) == PLANE)
			mrt->plane[--count[PLANE]] = ft_fill_plane(table->line);
		else if (eval_obj(table->line[0]) == CYLINDER)
			mrt->cylinder[--count[CYLINDER]] = ft_fill_cylinder(table->line);
		table = table->next;
	}
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
	table = ft_fill_table(fd);
	ft_close_fd(&fd);
	ft_count_objs(table, mrt->obj_count);
	ft_fill_objs(mrt, table, (int *)ft_memcpy((void *)mrt->obj_count, \
	sizeof(int) * 6));
	ft_free_table(table);
	return (0);
}
