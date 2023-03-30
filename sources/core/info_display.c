/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:23:17 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/29 23:48:40 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_get_index_str(int type, int index)
{
	char	*str;

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
	if (type == LIGHT)
		str = ft_strdup("LIGHT");
	return (ft_strjoin(ft_strjoin("OBJECT: ", str), idx));
}

void	display_strings(t_mrt *mrt)
{
	char	*object;
	char	*color;

	object = ft_get_object_str(mrt->curr_obj.type, mrt->curr_obj.index);
	color = ft_strjoin("color: ", ft_get_color_str(ft_get_obj_color(mrt, \
	mrt->curr_obj.type, mrt->curr_obj.index)));
	mlx_string_put(mrt->mlx, mrt->win, 10, 20, 0xFFFFFF, \
	"--------MiniRT--------");
	mlx_string_put(mrt->mlx, mrt->win, 10, 40, 0xFFFFFF, "Controls:");
	mlx_string_put(mrt->mlx, mrt->win, 10, 60, 0xFFFFFF, "WASDQE - move cam");
	mlx_string_put(mrt->mlx, mrt->win, 10, 80, 0xFFFFFF, "Arrows - rotate cam");
	mlx_string_put(mrt->mlx, mrt->win, 10, 100, 0xFFFFFF, "Z - save scene");
	mlx_string_put(mrt->mlx, mrt->win, 10, 120, 0xFFFFFF, "X - save image");
	mlx_string_put(mrt->mlx, mrt->win, 10, 140, 0xFFFFFF, "ESC - exit");
	mlx_string_put(mrt->mlx, mrt->win, 10, 160, 0xFFFFFF, \
	"Click to select objs");
	mlx_string_put(mrt->mlx, mrt->win, 10, 180, 0xFFFFFF, \
	"----------------------");
	mlx_string_put(mrt->mlx, mrt->win, 10, 210, 0xFFFFFF, object);
	mlx_string_put(mrt->mlx, mrt->win, 10, 230, 0xFFFFFF, color);
}
