/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:33:43 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/16 03:34:10 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_opposite_color(t_rgb color)
{
	t_rgb	ret;

	ret.r = 255 - color.r;
	ret.g = 255 - color.g;
	ret.b = 255 - color.b;
	ret = normalize_color(ret);
	return (ret);
}
