/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:18:20 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/27 21:43:15 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_to_file(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

char	*ft_write_pos(t_vec pos)
{
	char	*line;

	line = ft_strjoin(ft_ftoa(pos.x), ",");
	line = ft_strjoin(line, ft_ftoa(pos.y));
	line = ft_strjoin(line, ",");
	line = ft_strjoin(line, ft_ftoa(pos.z));
	return (line);
}

char	*ft_write_rgb(t_rgb color)
{
	char	*line;

	line = ft_strjoin(ft_itoa(color.r), ",");
	line = ft_strjoin(line, ft_itoa(color.g));
	line = ft_strjoin(line, ",");
	line = ft_strjoin(line, ft_itoa(color.b));
	return (line);
}

void	ft_write_amblight(t_light amblight, int fd)
{
	char	*line;

	line = ft_strjoin("A ", ft_ftoa(amblight.ratio));
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, ft_write_rgb(amblight.color));
	ft_write_to_file(line, fd);
	ft_free(line);
}

void	ft_write_camera(t_cam cam, int fd)
{
	char	*line;

	line = ft_strjoin("c ", ft_write_pos(cam.dir));
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, ft_write_pos(cam.pos));
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, ft_itoa(cam.fov));
	ft_write_to_file(line, fd);
	ft_free(line);
}

void	save_scene(t_mrt *mrt)
{
	int		fd;
	char	*line;

	fd = open("scene.rt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Error opening file", "scene.rt", NULL);
	ft_write_amblight(mrt->amblight, fd);
	ft_write_camera(mrt->cam, fd);
	// ft_write_lights(mrt->light, mrt->obj_count[LIGHT], fd);
	// ft_write_planes(mrt->plane, mrt->obj_count[PLANE], fd);
	// ft_write_spheres(mrt->sphere, mrt->obj_count[SPHERE], fd);
	// ft_write_cylinders(mrt->cylinder, mrt->obj_count[CYLINDER], fd);
}
