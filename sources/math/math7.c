/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:54:16 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/16 05:35:08 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mtrx	define_rot_mtrx(t_vec rot_axis, double sin, double cos)
{
	t_mtrx	ret;

	ret.r1 = fill_coord(cos + (int_pow(rot_axis.x, 2) * (1 - cos)),
			(rot_axis.x * rot_axis.y * (1 - cos)) - (rot_axis.z * sin),
			(rot_axis.x * rot_axis.z * (1 - cos)) + (rot_axis.y * sin));
	ret.r2 = fill_coord((rot_axis.x * rot_axis.y * (1 - cos))
			+ (rot_axis.z * sin), cos + (int_pow(rot_axis.y, 2)
				* (1 - cos)), (rot_axis.y * rot_axis.z * (1 - cos))
			- (rot_axis.x * sin));
	ret.r3 = fill_coord((rot_axis.x * rot_axis.z * (1 - cos))
			- (rot_axis.y * sin), (rot_axis.y * rot_axis.z * (1 - cos))
			+ (rot_axis.x * sin), cos + (int_pow(rot_axis.z, 2)
				* (1 - cos)));
	return (ret);
}
