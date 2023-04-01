/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:18:20 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/01 20:30:50 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_amblight(t_light amblight, int fd)
{
	char	*line;

	line = ft_strjoin("A\t\t", ft_ftoa(amblight.ratio));
	line = ft_strjoin(line, "\t\t");
	line = ft_strjoin(line, ft_write_rgb(amblight.color));
	ft_write_to_file(line, fd);
	ft_free(line);
}

void	ft_write_camera(t_cam cam, int fd)
{
	char	*line;

	line = ft_strjoin("C\t\t", ft_write_pos(cam.pos));
	line = ft_strjoin(line, "\t\t");
	line = ft_strjoin(line, ft_write_dir(cam.dir));
	line = ft_strjoin(line, "\t\t");
	line = ft_strjoin(line, ft_itoa(cam.fov));
	ft_write_to_file(line, fd);
	ft_free(line);
}

void	ft_write_lights(t_light *light, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	ft_write_to_file("", fd);
	while (i < count)
	{
		line = ft_strjoin("L\t\t", ft_write_pos(light[i].pos));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_ftoa(light[i].ratio));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_write_rgb(light[i].color));
		ft_write_to_file(line, fd);
		ft_free(line);
		i++;
	}
	ft_write_to_file("", fd);
}

void	save_scene(t_mrt *mrt)
{
	int		fd;

	fd = open("scene.rt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Error opening file", "scene.rt", NULL);
	ft_write_amblight(mrt->amblight, fd);
	ft_write_camera(mrt->cam, fd);
	ft_write_lights(mrt->light, mrt->obj_count[LIGHT], fd);
	ft_write_planes(mrt->plane, mrt->obj_count[PLANE], fd);
	ft_write_spheres(mrt->sphere, mrt->obj_count[SPHERE], fd);
	ft_write_cylinders(mrt->cylinder, mrt->obj_count[CYLINDER], fd);
	ft_write_triangles(mrt->triangle, mrt->obj_count[TRIANGLE], fd);
	close(fd);
}
