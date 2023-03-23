/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:23:17 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/22 22:24:26 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_get_index_str(int type, int index)
{
	char	*str;
	char	*tmp;

	if (type == CAMERA)
		return (ft_strdup(""));
	str = ft_strjoin(ft_strdup(" "), ft_itoa(index + 1));
	return (str);
}

char	*ft_get_object_str(int type, int index)
{
	char	*str;
	char	*idx;

	str = ft_strdup("UNKNOWN");
	idx = ft_get_index_str(type, index);
	if (type == SPHERE)
		str = ft_strdup("SPHERE");
	if (type == PLANE)
		str = ft_strdup("PLANE");
	if (type == CYLINDER)
		str = ft_strdup("CYLINDER");
	if (type == CAMERA)
		str = ft_strdup("CAMERA");
	return (ft_strjoin(ft_strjoin("OBJECT: ", str), idx));
}

char	*ft_get_color_str(t_rgb color)
{
	char	*line;
	int		fd;
	t_rgb	rgb;
	int		diff;
	char	*str;

	diff = 255 * 3;
	fd = open("rgb.txt", O_RDONLY, 0644);
	line = get_next_line(fd);
	str = ft_strdup("UNKNOWN");
	while (line)
	{
		rgb.r = ft_atoi(line);
		rgb.g = ft_atoi(line + 4);
		rgb.b = ft_atoi(line + 8);
		if (ft_abs(color.r - rgb.r) + ft_abs(color.g - rgb.g) + \
		ft_abs(color.b - rgb.b) < diff)
		{
			diff = ft_abs(color.r - rgb.r) + ft_abs(color.g - rgb.g) \
			+ ft_abs(color.b - rgb.b);
			str = ft_strdup(line + 13);
		}
		ft_free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (str);
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
	return (color);
}

void	display_strings(t_mrt *mrt)
{
	char	*object;
	char	*color;

	object = ft_get_object_str(mrt->curr_obj.type, mrt->curr_obj.index);
	color = ft_get_color_str(ft_get_obj_color(mrt, mrt->curr_obj.type, \
	mrt->curr_obj.index));
	mlx_clear_window(mrt->mlx, mrt->win);
	mlx_string_put(mrt->mlx, mrt->win, 10, 20, 0xFFFFFF, "MiniRT");
	mlx_string_put(mrt->mlx, mrt->win, 10, 40, 0xFFFFFF, "Controls:");
	mlx_string_put(mrt->mlx, mrt->win, 10, 60, 0xFFFFFF, "WASDQE - move");
	mlx_string_put(mrt->mlx, mrt->win, 10, 80, 0xFFFFFF, "Arrows - rotate");
	mlx_string_put(mrt->mlx, mrt->win, 10, 100, 0xFFFFFF, "Scroll - zoom");
	mlx_string_put(mrt->mlx, mrt->win, 10, 120, 0xFFFFFF, "ESC - exit");
	mlx_string_put(mrt->mlx, mrt->win, 10, 200, 0xFFFFFF, object);
	mlx_string_put(mrt->mlx, mrt->win, 10, 220, 0xFFFFFF, color);
}
