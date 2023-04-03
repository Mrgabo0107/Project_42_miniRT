/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:54:42 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/02 19:54:58 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_options(t_option option, int fd)
{
	char	*line;

	line = ft_strjoin_free(("mir "), ft_ftoa(option.mirror));
	ft_write_to_file(line, fd);
	ft_free(line);
	line = ft_strjoin_free(("spec "), ft_ftoa(option.specular[0]));
	line = ft_strjoin_free(line, (" "));
	line = ft_strjoin_free(line, ft_ftoa(option.specular[1]));
	ft_write_to_file(line, fd);
	ft_free(line);
	line = ft_strjoin_free(("check "), ft_write_rgb(option.check_color));
	line = ft_strjoin_free(line, (" "));
	line = ft_strjoin_free(line, ft_ftoa(option.chess_ctrl));
	ft_write_to_file(line, fd);
	ft_free(line);
}

void	ft_write_planes(t_plane *plane, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < count)
	{
		ft_write_to_file(ft_strjoin_free(("#"), ft_itoa(i + 1)), fd);
		line = ft_strjoin_free(("pl\t\t"), ft_write_pos(plane[i].pos));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_dir(plane[i].dir));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_rgb(plane[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(plane[i].option, fd);
		ft_free(line);
		ft_write_to_file("", fd);
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
		ft_write_to_file(ft_strjoin_free(("#"), ft_itoa(i + 1)), fd);
		line = ft_strjoin_free(("sp\t\t"), ft_write_pos(sphere[i].center));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_ftoa(sphere[i].radius * 2));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_rgb(sphere[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(sphere[i].option, fd);
		ft_free(line);
		ft_write_to_file("", fd);
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
		ft_write_to_file(ft_strjoin_free(("#"), ft_itoa(i + 1)), fd);
		line = ft_strjoin_free(("cy\t\t"), ft_write_pos(cylinder[i].pos));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_dir(cylinder[i].dir));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_ftoa(cylinder[i].radius * 2));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_ftoa(cylinder[i].height));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_rgb(cylinder[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(cylinder[i].option, fd);
		ft_free(line);
		ft_write_to_file("", fd);
		i++;
	}
}

void	ft_write_triangles(t_triangle *triangle, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < count)
	{
		ft_write_to_file(ft_strjoin_free(("#"), ft_itoa(i + 1)), fd);
		line = ft_strjoin_free(("tr\t\t"), ft_write_pos(triangle[i].p1));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_pos(triangle[i].p2));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_pos(triangle[i].p3));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_rgb(triangle[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(triangle[i].option, fd);
		ft_free(line);
		ft_write_to_file("", fd);
		i++;
	}
}
