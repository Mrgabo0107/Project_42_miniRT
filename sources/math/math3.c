/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:44:14 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/24 05:04:3 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_rest(t_vec v1, t_vec v2)
{
	return (vec_sum(v1, scal_vec(-1, v2)));
}

double  max_v(double d1, double d2)
{
    if (d1 >= d2)
        return (d1);
    return (d2);    
}

double  norm_raised_2(t_vec v)
{
	double	ret;

	ret = int_pow(v.x, 2) + int_pow(v.y, 2) + int_pow(v.z, 2);
	return (ret);
}

t_vec	mtrx_by_vec(t_mtrx m, t_vec v)
{
	t_vec	ret;

	ret.x = dot_prod(m.r1, v);
	ret.y = dot_prod(m.r2, v);
	ret.z = dot_prod(m.r3, v);
	return (ret);
}

// t_mtrx	invert_mtrx(t_mtrx m)
// {
// 	double	coef;
// 	t_mtrx	ret;

// 	coef = 1 / mtrx_det(m);
// 	ret = mtrx_trsp(m);

// 	return (ret);
// }