/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:18:20 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/02 19:54:58 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_amblight(t_light amblight, int fd)
{
	char	*line;

	line = ft_strjoin_free(("A\t\t"), ft_ftoa(amblight.ratio));
	line = ft_strjoin_free(line, ("\t\t"));
	line = ft_strjoin_free(line, ft_write_rgb(amblight.color));
	ft_write_to_file(line, fd);
	ft_free(line);
}

void	ft_write_camera(t_cam cam, int fd)
{
	char	*line;

	line = ft_strjoin_free(("C\t\t"), ft_write_pos(cam.pos));
	line = ft_strjoin_free(line, ("\t\t"));
	line = ft_strjoin_free(line, ft_write_dir(cam.dir));
	line = ft_strjoin_free(line, ("\t\t"));
	line = ft_strjoin_free(line, ft_itoa(cam.fov));
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
		ft_write_to_file(ft_strjoin_free(("#"), ft_itoa(i + 1)), fd);
		line = ft_strjoin_free(("L\t\t"), ft_write_pos(light[i].pos));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_ftoa(light[i].ratio));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_rgb(light[i].color));
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
