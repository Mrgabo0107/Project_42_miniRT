/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_names.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:13:47 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/02 19:54:58 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_ratio_rgb(t_rgb color)
{
	double	max;

	max = color.r;
	if (color.g > max)
		max = color.g;
	if (color.b > max)
		max = color.b;
	if (max > 1)
	{
		color.r *= 1 / max;
		color.g *= 1 / max;
		color.b *= 1 / max;
	}
	return (color);
}

char	*white_grey_black(t_rgb color)
{
	int	tmp;

	tmp = color.r + color.g + color.b;
	if (tmp > 150 && tmp < 678)
		return (("grey"));
	if (tmp > 678)
		return (("white"));
	return (("black"));
}

char	*ft_get_color_str(t_rgb color)
{
	char	*line;
	int		fd;
	double	diff;
	char	*str;

	str = NULL;
	diff = 255 * 3;
	fd = open("rgb.txt", O_RDONLY, 0644);
	line = get_next_line(fd);
	if (color.r == color.g && color.g == color.b)
		return (white_grey_black(color));
	color = get_ratio_rgb(color);
	while (line)
	{
		if (v_abs(color.r - ft_atof(line)) + v_abs(color.g - \
		ft_atof(line + 4)) + v_abs(color.b - ft_atof(line + 8)) < diff)
		{
			diff = v_abs(color.r - ft_atof(line)) + v_abs(color.g - \
			ft_atof(line + 4)) + v_abs(color.b - ft_atof(line + 8));
			str = (line + 13);
		}
		ft_free(line);
		line = get_next_line(fd);
	}
	return (close(fd), str);
}

t_rgb	ft_get_obj_color(t_mrt *mrt, int type, int index)
{
	t_rgb	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (type == SPHERE)
		color = mrt->sphere[index].color;
	if (type == PLANE)
		color = mrt->plane[index].color;
	if (type == CYLINDER)
		color = mrt->cylinder[index].color;
	if (type == LIGHT)
		color = mrt->light[index].color;
	return (color);
}
