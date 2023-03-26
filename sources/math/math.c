/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:53:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/26 23:40:28 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	int_pow(double basis, int exp)
{
	int		i;
	double	res;

	res = 1;
	i = 0;
	while (i < exp)
	{
		res *= basis;
		i++;
	}
	return (res);
}

double	vect_norm(t_vec v)
{
	double	sum_sqr;

	sum_sqr = int_pow(v.x, 2) + int_pow(v.y, 2) + int_pow(v.z, 2);
	return (sqrt(sum_sqr));
}

t_vec	normalize(t_vec v)
{
	t_vec	ret;
	double	norm;

	norm = vect_norm(v);
	ret.x = v.x / norm;
	ret.y = v.y / norm;
	ret.z = v.z / norm;
	return (ret);
}

t_vec	vector_sum(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}
