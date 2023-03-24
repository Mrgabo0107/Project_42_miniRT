/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:54:16 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/23 06:47:23 by gamoreno         ###   ########.fr       */
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

double	integer_part(double n)
{
	double	integer_part;
	double	decimal_part;

	decimal_part = modf(n, &integer_part);
	return (integer_part);
}

double	get_azimuth(t_vec orig)
{
	double	ret;

	if (orig.z > 0)
		ret = atan(sqrt(int_pow(orig.x, 2) + int_pow(orig.y, 2)) / orig.z);
	if (orig.z == 0)
		ret = PI / 2;
	if (orig.z < 0)
		ret = PI + atan(sqrt(int_pow(orig.x, 2)
					+ int_pow(orig.y, 2)) / orig.z);
	return (ret);
}

t_vec	get_spheric_coord(t_vec orig)
{
	t_vec	ret;

	ret.x = vect_norm(orig);
	ret.y = get_azimuth(orig);
	if (orig.x > 0)
	{
		if (orig.y > 0)
			ret.z = atan(orig.y / orig.x);
		if (orig.y < 0)
			ret.z = (2 * PI) + atan(orig.y / orig.x);
	}
	if (orig.x == 0)
	{
		if (orig.y > 0)
			ret.z = PI / 2;
		if (orig.y < 0)
			ret.z = -PI / 2;
	}
	if (orig.x < 0)
		ret.z = PI + atan(orig.y / orig.x);
	return (ret);
}

t_vec	get_cyl_coor(t_vec orig)
{
	t_vec	ret;

	ret.x = sqrt(int_pow(orig.x, 2) + int_pow(orig.y, 2));
	if (orig.x != 0)
	{
		ret.y = atan(orig.y / orig.x);
		if (ret.y < 0)
			ret.y += PI;
	}
	else
	{
		if (orig.y > 0)
			ret.y = PI;
		if (orig.y < 0)
			ret.y = -PI;
	}
	ret.z = orig.z;
	return (ret);
}
