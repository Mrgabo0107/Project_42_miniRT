/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 07:14:15 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/05 21:36:23 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	mtrx_det(t_mtrx m)
{
	double	ret;

	ret = (m.r1.x * m.r2.y * m.r3.z) + (m.r2.x * m.r3.y * m.r1.z)
		+ (m.r3.x * m.r1.y * m.r2.z) - (m.r1.z * m.r2.y * m.r3.x)
		- (m.r2.z * m.r3.y * m.r1.x) - (m.r3.z * m.r1.y * m.r2.z);
	return (ret);
}

t_mtrx	mtrx_trsp(t_mtrx m)
{
	t_mtrx	ret;

	ret.r1 = fill_coord(m.r1.x, m.r2.x, m.r3.x);
	ret.r2 = fill_coord(m.r1.y, m.r2.y, m.r3.y);
	ret.r3 = fill_coord(m.r1.z, m.r2.z, m.r3.z);
	return (ret);
}

t_mtrx	mtrx_adj(t_mtrx m)
{
	t_mtrx	ret;

	ret.r1 = fill_coord((m.r2.y * m.r3.z) - (m.r3.y * m.r2.z),
			(m.r3.x * m.r2.z) - (m.r2.x * m.r3.z),
			(m.r2.x * m.r3.y) - (m.r3.x * m.r2.y));
	ret.r2 = fill_coord((m.r3.y * m.r1.z) - (m.r1.y * m.r3.z),
			(m.r1.x * m.r3.z) - (m.r3.x * m.r1.z),
			(m.r3.x * m.r1.y) - (m.r1.x * m.r3.y));
	ret.r3 = fill_coord((m.r1.y * m.r2.z) - (m.r2.y * m.r1.z),
			(m.r2.x * m.r1.z) - (m.r1.x * m.r2.z),
			(m.r1.x * m.r2.y) - (m.r2.x * m.r1.y));
	return (ret);
}

t_mtrx	scal_mtrx(double s, t_mtrx m)
{
	t_mtrx	ret;

	ret.r1 = scal_vec(s, m.r1);
	ret.r2 = scal_vec(s, m.r2);
	ret.r3 = scal_vec(s, m.r3);
	return (ret);
}
