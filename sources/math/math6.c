/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:54:16 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/13 20:55:12 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_base	first_rotation(t_vec dir, t_base can)
{
	double	sin_an;
	double	cos_an;
	t_vec	curr;
	t_base	ret;
	t_mtrx	chng_base;

	curr = vec_rest(dir, scal_vec(dir.y, can.n2));
	cos_an = dot_prod(can.n3, curr) / vect_norm(curr);
	sin_an = sqrt(1 - int_pow(cos_an, 2));
	if (dir.x < 0)
		sin_an *= -1;
	chng_base.r1 = fill_coord(cos_an, 0, sin_an);
	chng_base.r2 = fill_coord(0, 1, 0);
	chng_base.r3 = fill_coord(-sin_an, 0, cos_an);
	ret.n1 = mtrx_by_vec(chng_base, can.n1);
	ret.n2 = mtrx_by_vec(chng_base, can.n2);
	ret.n3 = mtrx_by_vec(chng_base, can.n3);
	return (ret);
}

static t_base	second_rotation(t_vec dir, t_base ret)
{
	double	sin_an;
	double	cos_an;
	t_base	retu;
	t_mtrx	chng_base;

	cos_an = dot_prod(dir, ret.n3);
	sin_an = -sqrt(1 - int_pow(cos_an, 2));
	if (dir.y < 0)
		sin_an *= -1;
	chng_base.r1 = fill_coord(cos_an + (int_pow(ret.n1.x, 2) * (1 - cos_an)),
			(ret.n1.x * ret.n1.y * (1 - cos_an)) - (ret.n1.z * sin_an),
			(ret.n1.x * ret.n1.z * (1 - cos_an)) + (ret.n1.y * sin_an));
	chng_base.r2 = fill_coord((ret.n1.x * ret.n1.y * (1 - cos_an))
			+ (ret.n1.z * sin_an), cos_an + (int_pow(ret.n1.y, 2)
				* (1 - cos_an)), (ret.n1.y * ret.n1.z * (1 - cos_an))
			- (ret.n1.x * sin_an));
	chng_base.r3 = fill_coord((ret.n1.x * ret.n1.z * (1 - cos_an))
			- (ret.n1.y * sin_an), (ret.n1.y * ret.n1.z * (1 - cos_an))
			+ (ret.n1.x * sin_an), cos_an + (int_pow(ret.n1.z, 2)
				* (1 - cos_an)));
	retu.n1 = mtrx_by_vec(chng_base, ret.n1);
	retu.n2 = mtrx_by_vec(chng_base, ret.n2);
	retu.n3 = mtrx_by_vec(chng_base, ret.n3);
	return (retu);
}

t_base	get_obj_base(t_vec	dir)
{
	t_base	ret;
	t_base	can;

	can.n1 = fill_coord(1, 0, 0);
	can.n2 = fill_coord(0, 1, 0);
	can.n3 = fill_coord(0, 0, 1);
	if (v_abs(dir.x) < 0.00001 && v_abs(dir.z) < 0.00001)
	{
		ret.n1 = can.n3;
		ret.n2 = can.n1;
		ret.n3 = can.n2;
		return (ret);
	}
	ret = first_rotation(dir, can);
	ret = second_rotation(dir, ret);
	return (ret);
}

