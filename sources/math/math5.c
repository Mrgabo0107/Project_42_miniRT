/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:20:39 by ana               #+#    #+#             */
/*   Updated: 2023/04/05 06:45:25 by gamoreno         ###   ########.fr       */
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

t_mtrx	fill_mtrx(t_vec v1, t_vec v2, t_vec v3)
{
	t_mtrx	ret;

	ret.r1 = v1;
	ret.r2 = v2;
	ret.r3 = v3;
	return (ret);
}

t_mtrx	init_base_mtrx(t_base *base)
{
	t_mtrx	ret;
	t_vec	curr;

	curr = fill_coord(base->n1.x, base->n2.x, base->n3.x);
	ret.r1 = curr;
	curr = fill_coord(base->n1.y, base->n2.y, base->n3.y);
	ret.r2 = curr;
	curr = fill_coord(base->n1.z, base->n2.z, base->n3.z);
	ret.r3 = curr;
	return (ret);
}

double	solve_quad(t_discr *info)
{
	double	op1;
	double	op2;
	double	ret;

	if (info->dscr < 0.00001)
		return (-info->b / (2 * info->a));
	op1 = (-info->b + sqrt(info->dscr)) / (2 * info->a);
	op2 = (-info->b - sqrt(info->dscr)) / (2 * info->a);
	ret = min_v(op1, op2);
	if (ret < 0)
		return (max_v(op1, op2));
	return (ret);
}
