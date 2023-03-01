/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:43:53 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/01 19:47:29 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	cross_prod(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

double	perp_to_plane(t_vec point, t_vec plane_point, t_vec plane_norm)
{
	double		distance;
	t_vec		plane_to_point;

	plane_to_point = vec_rest(point, plane_point);
	distance = v_abs(dot_prod(plane_to_point, plane_norm)
			/ vect_norm(plane_norm));
	return (distance);
}

t_mtrx fill_mtrx(t_vec v1, t_vec v2, t_vec v3)
{
	t_mtrx	ret;

	ret.r1 = v1;
	ret.r2 = v2;
	ret.r3 = v3;
	return (ret);
}