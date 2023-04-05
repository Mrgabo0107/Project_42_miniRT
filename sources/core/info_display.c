/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:23:17 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/05 04:55:07 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_get_index_str(int type, int index)
{
	char	*str;

	if (type == CAMERA)
		return ((""));
	str = ft_strjoin_free((" "), ft_itoa(index + 1));
	return (str);
}

char	*ft_get_object_str(int type, int index)
{
	char	*str;
	char	*idx;

	str = ("UNKNOWN");
	idx = ft_get_index_str(type, index);
	if (type == SPHERE)
		str = ("SPHERE");
	if (type == PLANE)
		str = ("PLANE");
	if (type == CYLINDER)
		str = ("CYLINDER");
	if (type == CAMERA)
		str = ("CAMERA");
	if (type == LIGHT)
		str = ("LIGHT");
	if (type == CONE)
		str = ("CONE");
	if (type == TRIANGLE)
		str = ("TRIANGLE");
	return (ft_strjoin_free(ft_strjoin_free(("OBJECT: "), \
	str), idx));
}

void	display_strings(t_mrt *mrt)
{
	char	*object;
	char	*color;

	object = ft_get_object_str(mrt->curr_obj.type, mrt->curr_obj.index);
	color = ft_strjoin_free("color: ", ft_get_color_str(ft_get_obj_color(mrt, \
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
	ft_free(object);
	ft_free(color);
}
