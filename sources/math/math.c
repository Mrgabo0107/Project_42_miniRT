/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:53:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/21 22:28:33 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*if ctrl == 0, it passes radians to degrees, else it passes degrees
to radians */
double	rad_and_deg(double angle, int ctrl)
{
	if (ctrl == 0)
		return ((angle * 180) / PI);
	else
		return ((angle * PI) / 180);
}

double	int_pow(double basis, int exp)
{
	int i;
	double	res;

	res = 1;
	i = 0;
	while(i < exp)
	{
		res *= basis;
		i++;
	}
	return (res);
}

t_vec	fill_coord(double c1, double c2, double c3)
{
	t_vec	res;

	res.x = c1;
	res.y = c2;
	res.z = c3;
	return (res);
}

double	vect_norm(t_vec v)
{
	double sum_sqr;

	sum_sqr = int_pow(v.x, 2) + int_pow(v.y, 2) + int_pow(v.z, 2);
	return (sqrt(sum_sqr));
}

t_vec	normalize(t_vec v)
{
	t_vec ret;
	double norm;

	norm = vect_norm(v);
	ret.x = v.x / norm;
	ret.y = v.y / norm;
	ret.z = v.z / norm;
	return (ret);
}
