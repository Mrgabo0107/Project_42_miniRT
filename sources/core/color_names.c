/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_names.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:13:47 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/07 19:49:04 by gamoreno         ###   ########.fr       */
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
	double	diff;
	char	**str;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	diff = 255 * 3;
	str = ft_split(COLORS, '\n');
	if (color.r == color.g && color.g == color.b)
		return (white_grey_black(color));
	color = get_ratio_rgb(color);
	while (str[i])
	{
		if (v_abs(color.r - ft_atof(str[i])) + v_abs(color.g - \
		ft_atof(str[i] + 4)) + v_abs(color.b - ft_atof(str[i] + 8)) < diff)
		{
			diff = v_abs(color.r - ft_atof(str[i])) + v_abs(color.g - \
			ft_atof(str[i] + 4)) + v_abs(color.b - ft_atof(str[i] + 8));
			ret = ft_strdup(str[i] + 13);
		}
		i++;
	}
	return (ret);
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
