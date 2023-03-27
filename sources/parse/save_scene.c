/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:18:20 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/27 23:49:43 by yridgway         ###   ########.fr       */
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

void	ft_write_options(t_option option, int fd)
{
	char	*line;

	line = ft_strjoin("mir ", ft_ftoa(option.mirror));
	ft_write_to_file(line, fd);
	ft_free(line);
	line = ft_strjoin("spec ", ft_ftoa(option.specular[0]));
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, ft_ftoa(option.specular[1]));
	ft_write_to_file(line, fd);
	ft_free(line);
	line = ft_strjoin("check ", ft_write_rgb(option.check_color));
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, ft_ftoa(option.chess_ctrl));
	ft_write_to_file(line, fd);
	ft_free(line);
}

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
	line = ft_strjoin(line, ft_write_pos(cam.dir));
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
}

void	ft_write_planes(t_plane *plane, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < count)
	{
		line = ft_strjoin("pl\t\t", ft_write_pos(plane[i].pos));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_write_pos(plane[i].dir));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_write_rgb(plane[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(plane[i].option, fd);
		ft_free(line);
		i++;
	}
}

void	ft_write_spheres(t_sphere *sphere, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < count)
	{
		line = ft_strjoin("sp\t\t", ft_write_pos(sphere[i].center));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_ftoa(sphere[i].radius * 2));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_write_rgb(sphere[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(sphere[i].option, fd);
		ft_free(line);
		i++;
	}
}

void	ft_write_cylinders(t_cylinder *cylinder, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < count)
	{
		line = ft_strjoin("cy\t\t", ft_write_pos(cylinder[i].pos));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_write_pos(cylinder[i].dir));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_ftoa(cylinder[i].radius * 2));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_ftoa(cylinder[i].height));
		line = ft_strjoin(line, "\t\t");
		line = ft_strjoin(line, ft_write_rgb(cylinder[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(cylinder[i].option, fd);
		ft_free(line);
		i++;
	}
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
	ft_write_lights(mrt->light, mrt->obj_count[LIGHT], fd);
	ft_write_planes(mrt->plane, mrt->obj_count[PLANE], fd);
	ft_write_spheres(mrt->sphere, mrt->obj_count[SPHERE], fd);
	ft_write_cylinders(mrt->cylinder, mrt->obj_count[CYLINDER], fd);
}
